#ifndef PLOTPANE_H
#define PLOTPANE_H

#include <list>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "../envtools/envtools.h"
#include "../softenv.h"
#include <iostream>

struct PlotPaneTitle
{
    public:
        std::string text;
        int yoffset;
        int xoffset;
        int size;
};

/// @brief Build a collection of drawable elements representing a plot
class PlotPane
{
    public:
        PlotPane(int xpos, int ypos, int width, int height, int xticks, int yticks, int xlabels, PlotPaneTitle title);
        std::list<sf::Drawable*>* GetDrawElements(){return &elements;};
        std::list<sf::Drawable*>* GetSeriesLines(){return &seriesElements;};
        int AddSeries(std::vector<double> *xvalues, std::vector<double> *yvalues, int samplescount, sf::Color color);
        int SetXYReferenceSerie(std::vector<double>* xvalues, std::vector<double>* yvalues, int samplescount);

    private:
        int width;
        int height;
        int xpos;
        int ypos;
        int xticks;
        int yticks;
        double* xvalues;
        double* yvalues;
        int xlabels; //total number of labels on the x axis
        double yvscale;
        double x_resolution;
        double xmatch;
        double ymax;
        double ymin;
        double xdelta;
        double ydelta;
        PlotPaneTitle paneTitle;

        std::list<sf::Drawable*> elements;
        std::list<sf::Drawable*> seriesElements;
        sf::Font paneFont;
        sf::Text* CenteredOriginText(std::string text, sf::Font font, int size, sf::Color textColor);
        sf::Text* CenteredLeftText(std::string text, sf::Font font, int size, sf::Color textColor);
        void DrawPane(std::vector<double>* xvalues, std::vector<double>* yvalues, int samplescount, int xlabels, PlotPaneTitle title);
};

#endif