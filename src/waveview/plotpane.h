#ifndef PLOTPANE_H
#define PLOTPANE_H

#include <list>
#include <SFML/Graphics.hpp>
#include <algorithm>

/// @brief Build a collection of drawable elements representing a plot
class PlotPane
{
    public:
        PlotPane(int xpos, int ypos, int width, int height, int xticks, int yticks);
        std::list<sf::Drawable*>* GetDrawElements(){return &elements;};
        std::list<sf::Drawable*>* GetSeriesLines(){return &seriesElements;};
        void AddSeries(std::vector<double>* xvalues, std::vector<double>* yvalues, int samplescount, sf::Color color);
        
    private:
        int width;
        int height;
        int xpos;
        int ypos;
        double* xvalues;
        double* yvalues;
        
        std::list<sf::Drawable*> elements;
        std::list<sf::Drawable*> seriesElements;
};

#endif