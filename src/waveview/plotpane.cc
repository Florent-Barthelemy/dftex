#include "plotpane.h"

PlotPane::PlotPane(int xpos, int ypos, int width, int height, int xticks, int yticks, int xlabels, PlotPaneTitle title)
{
    this->width = width;
    this->height = height;
    this->xpos = xpos;
    this->ypos = ypos;
    this->xticks = xticks;
    this->yticks = yticks;

    this->xvalues = nullptr;
    this->yvalues = nullptr;

    this->paneTitle = title;
    this->xlabels = xlabels;

    // Setting up font for this plot pane
    std::string fontfolder = EnvTools::GetEnvVar(WV_VARENV_FONT_FOLDER);
    std::string fontname = WV_NAME_FONT_DEFAULT;
    paneFont.loadFromFile(fontfolder + fontname);
}

sf::Text *PlotPane::CenteredOriginText(std::string text, sf::Font font, int size, const sf::Color textColor)
{
    sf::Text *textObj = new sf::Text(text, paneFont);
    textObj->setFillColor(textColor);
    textObj->setCharacterSize(size);
    sf::FloatRect textRect = textObj->getLocalBounds();
    textObj->setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

    return textObj;
}

sf::Text *PlotPane::CenteredLeftText(std::string text, sf::Font font, int size, const sf::Color textColor)
{
    sf::Text *textObj = new sf::Text(text, paneFont);
    textObj->setFillColor(textColor);
    textObj->setCharacterSize(size);
    sf::FloatRect textRect = textObj->getLocalBounds();
    textObj->setOrigin(textRect.left, textRect.height);

    return textObj;
}

void PlotPane::DrawPane(std::vector<double> *xvalues, std::vector<double> *yvalues, int samplescount, int xlabels, PlotPaneTitle title)
{
    // Title text
    sf::Text *tickText = CenteredOriginText(title.text, paneFont, title.size, sf::Color::White);
    tickText->setPosition(sf::Vector2f((xpos + width / 2) + title.xoffset, ypos - 10 - title.yoffset));
    elements.push_back(tickText);

    // Left box line
    sf::Color tickLinesColor(100, 100, 100);
    sf::RectangleShape *line_l = new sf::RectangleShape(sf::Vector2f(height, 1));
    line_l->setPosition(xpos, ypos);
    line_l->rotate(90);
    line_l->setFillColor(tickLinesColor);

    // Top box line
    sf::RectangleShape *line_t = new sf::RectangleShape(sf::Vector2f(width, 1));
    line_t->setPosition(xpos, ypos);
    line_t->rotate(0);
    line_t->setFillColor(tickLinesColor);

    // Right box line
    sf::RectangleShape *line_r = new sf::RectangleShape(sf::Vector2f(height, 1));
    line_r->setPosition(xpos + width, ypos);
    line_r->rotate(90);
    line_r->setFillColor(tickLinesColor);

    // Bottom box line
    sf::RectangleShape *line_b = new sf::RectangleShape(sf::Vector2f(width, 1));
    line_b->setPosition(xpos, ypos + height);
    line_b->rotate(0);
    line_b->setFillColor(tickLinesColor);

    elements.push_back(line_l);
    elements.push_back(line_r);
    elements.push_back(line_t);
    elements.push_back(line_b);

    // Creating x tickMarks
    int tickSpacing = width / xticks;
    int currentTickPos = tickSpacing;
    for (int i = 0; i < xticks; i++)
    {
        sf::RectangleShape *tickLine = new sf::RectangleShape(sf::Vector2f(height, 1));
        tickLine->setPosition(xpos + currentTickPos, ypos);
        tickLine->rotate(90);
        tickLine->setFillColor(tickLinesColor);

        elements.push_back(tickLine);

        currentTickPos += tickSpacing;
    }

    // Creating y tickMarks
    tickSpacing = height / yticks;
    currentTickPos = tickSpacing;
    for (int i = 0; i < yticks; i++)
    {
        sf::RectangleShape *tickLine = new sf::RectangleShape(sf::Vector2f(width, 1));
        tickLine->setPosition(xpos, ypos + currentTickPos);
        tickLine->rotate(0);
        tickLine->setFillColor(tickLinesColor);

        elements.push_back(tickLine);
        currentTickPos += tickSpacing;
    }

    double xmax = *std::max_element(xvalues->begin(), xvalues->end());
    double xmin = *std::min_element(xvalues->begin(), xvalues->end());

    // Creating ticks
    int labelPosIncrement = width / (xlabels - 1);
    int labelPos = xpos;
    double xvscale = samplescount / width;

    std::string tickt;

    for (int i = 0; i < xlabels; i++)
    {
        tickt = std::to_string(xvalues->at((labelPos - xpos) * xvscale));

        // Creating tick text
        sf::Text *tt = CenteredOriginText(tickt, paneFont, 15, sf::Color::White);
        tt->setPosition(sf::Vector2f(labelPos, ypos + height + 10));
        elements.push_back(tt);

        // updating next text position
        labelPos += labelPosIncrement;
    }
}

int PlotPane::SetXYReferenceSerie(std::vector<double> *xvalues, std::vector<double> *yvalues, int samplescount)
{
    DrawPane(xvalues, yvalues, samplescount, xlabels, paneTitle);
    // Compute coordinates sizing factors
    ymax = *std::max_element(yvalues->begin(), yvalues->end());
    ymin = *std::min_element(yvalues->begin(), yvalues->end());
    xdelta = *std::max_element(xvalues->begin(), xvalues->end()) - *std::min_element(xvalues->begin(), xvalues->end());
    ydelta = *std::max_element(yvalues->begin(), yvalues->end()) - *std::min_element(yvalues->begin(), yvalues->end());
    // double xvscale = width/xdelta;

    if(ydelta == 0)
        yvscale = 0;
    else
        yvscale = height / ydelta;

    x_resolution = xdelta / width;
    xmatch = width * 1.0 / samplescount;

    return 0;
}

int PlotPane::AddSeries(std::vector<double> *xvalues, std::vector<double> *yvalues, int samplescount, sf::Color color)
{
    // This function will do shit if X values are not strictly increasing monotonic
    // Should check if X axis is strictly monotonic

    // Compute coordinates sizing factors
    // double xmin = *std::min_element(xvalues->begin(), xvalues->end());
    bool serieOutsideBoundsNotified = false;
    double _ymax = *std::max_element(yvalues->begin(), yvalues->end());
    double _ymin = *std::min_element(yvalues->begin(), yvalues->end());
    // double xvscale = width/xdelta;
    // double yvscale = height / ydelta;

    // double x_resolution = xdelta / width;
    // double xmatch = width * 1.0 / samplescount;

    int geometries = 0;

    int xpixel = 0;
    int ypix_from;
    int ypix_to;
    double xstart_indx = 0;
    double local_min = _ymax;
    double local_max = _ymin;

    // Add a contingent pixel filter

    for (int i = xstart_indx; i < samplescount; i++)
    {
        double yval = yvalues->at(i);

        // Find the next point untill resolution is reached
        if ((xvalues->at(i) - xvalues->at(xstart_indx)) > x_resolution)
        {
            // Stop. Save Xpixel, Y points

            //Don't question the following, trust the magic
            ypix_from = (ymax - local_max) * yvscale + ypos;
            ypix_to = (ymax - local_min) * yvscale + ypos;

            

            for (int ii = ypix_from; ii <= ypix_to; ii++)
            {
                sf::RectangleShape *rect = new sf::RectangleShape();
                rect->setSize(sf::Vector2f(1, 1));
                rect->setFillColor(color);

                rect->setPosition(xpixel + xpos, ii);

                if (ii > height + ypos || ii < ypos || xpixel > width || xpixel < 0)
                {
                    if (!serieOutsideBoundsNotified)
                    {
                        std::cout << "\n[WV INFO] : A serie is outside bounds\n"
                                  << std::endl;
                        serieOutsideBoundsNotified = true;
                    }
                }
                else
                    seriesElements.push_back(rect);

                geometries++;
            }

            // Reset local extremums search values
            local_min = _ymax;
            local_max = _ymin;

            // Restart search indexes
            xstart_indx = i;
            xpixel = i * xmatch;
        }

        // local min and max are used to plot the constant x line

        // update local min
        if (yval < local_min)
            local_min = yval;

        // Update local max
        if (yval > local_max)
            local_max = yval;
    }

    return geometries;
}