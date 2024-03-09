#include "plotpane.h"

PlotPane::PlotPane(int xpos, int ypos, int width, int height, int xticks, int yticks)
{
    this->width = width;
    this->height = height;
    this->xpos = xpos;
    this->ypos = ypos;

    //Left box line
    sf::Color tickLinesColor(100, 100, 100);
    sf::RectangleShape* line_l = new sf::RectangleShape(sf::Vector2f(height, 1));
    line_l->setPosition(xpos, ypos);
    line_l->rotate(90);
    line_l->setFillColor(tickLinesColor);

    //Top box line
    sf::RectangleShape* line_t = new sf::RectangleShape(sf::Vector2f(width, 1));
    line_t->setPosition(xpos, ypos);
    line_t->rotate(0);
    line_t->setFillColor(tickLinesColor);

    //Right box line
    sf::RectangleShape* line_r = new sf::RectangleShape(sf::Vector2f(height, 1));
    line_r->setPosition(xpos + width, ypos);
    line_r->rotate(90);
    line_r->setFillColor(tickLinesColor);

    //Bottom box line
    sf::RectangleShape* line_b = new sf::RectangleShape(sf::Vector2f(width, 1));
    line_b->setPosition(xpos, ypos + height);
    line_b->rotate(0);
    line_b->setFillColor(tickLinesColor);

    elements.push_back(line_l);
    elements.push_back(line_r);
    elements.push_back(line_t);
    elements.push_back(line_b);

    //Creating x tickMarks
    int tickSpacing = width/xticks;
    int currentTickPos = tickSpacing;
    for(int i = 0; i < xticks; i++)
    {
        sf::RectangleShape* tickLine = new sf::RectangleShape(sf::Vector2f(height, 1));
        tickLine->setPosition(xpos + currentTickPos, ypos);
        tickLine->rotate(90);
        tickLine->setFillColor(tickLinesColor);

        elements.push_back(tickLine);

        currentTickPos += tickSpacing;
    }

    //Creating y tickMarks
    tickSpacing = height/yticks;
    currentTickPos = tickSpacing;
    for(int i = 0; i < yticks; i++)
    {
        sf::RectangleShape* tickLine = new sf::RectangleShape(sf::Vector2f(width, 1));
        tickLine->setPosition(xpos, ypos + currentTickPos);
        tickLine->rotate(0);
        tickLine->setFillColor(tickLinesColor);

        elements.push_back(tickLine);

        currentTickPos += tickSpacing;
    }
}

void PlotPane::AddSeries(std::vector<double>* xvalues, std::vector<double>* yvalues, int samplescount, sf::Color color)
{
    //This function will do shit if X values are not strictly increasing monotonic

    //Should check if X axis is strictly monotonic
    
    //Compute corrdinates sizing factors
    double xmin = *std::min_element(xvalues->begin(), xvalues->end());
    double ymax = *std::max_element(yvalues->begin(), yvalues->end());
    double ymin = *std::min_element(yvalues->begin(), yvalues->end());
    double xdelta = *std::max_element(xvalues->begin(), xvalues->end()) -  *std::min_element(xvalues->begin(), xvalues->end());
    double ydelta = *std::max_element(yvalues->begin(), yvalues->end()) - *std::min_element(yvalues->begin(), yvalues->end());
    double xvscale = width/xdelta;
    double yvscale = height/ydelta;


    double x_resolution = xdelta/width;
    double y_resolution = ydelta/width;

    int xpixel = 0;
    double eps = 0;
    double xstart_indx = 0;

    for(int i = xstart_indx; i < samplescount; i++)
    {
        //Find the next point untill resolution is reached
        eps = xvalues->at(xstart_indx) - xvalues->at(i);

        if(eps > x_resolution){
            //Stop. Save Xpixel, Y points


            xstart_indx = i;
            xpixel++;
        }
    
    }


    for(int i = 0; i < samplescount; i++)
    {
        sf::RectangleShape* rect = new sf::RectangleShape();
        rect->setSize(sf::Vector2f(1, 6));
        rect->setFillColor(color);
        rect->setPosition((xvalues->at(i) - xmin)*xvscale + xpos, (ymax - yvalues->at(i))*yvscale + ypos);
        

        seriesElements.push_back(rect);
    }
}