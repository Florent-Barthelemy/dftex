#ifndef WAVEVIEW_H
#define WAVEVIEW_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <string.h>
#include <list>
#include <iostream>
#include "../envtools/envtools.h"
#include "../softenv.h"
#include "plotpane.h"

struct WaveViewerConfig
{
    public:
     int xsize;
     int ysize;
     sf::String winTitle;
};

class WaveViewer
{
    public:
        explicit WaveViewer(WaveViewerConfig cfg) : config(cfg) {}

        /// @brief Launches the viewer window with specified fps limit. -1 = no limit
        void Launch(int);

        void AddPlotPane(PlotPane plot);
        
    private:
        sf::Text winInfoText;
        WaveViewerConfig config;
        std::list<sf::Drawable*> toDraw;
        std::list<sf::Drawable*> linesToDraw;
        sf::Vector2u winSize;
        void Redraw(sf::RenderWindow& win);

};

#endif