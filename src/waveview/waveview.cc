#include "waveview.h"

void WaveViewer::AddPlotPane(PlotPane plot)
{
    toDraw.merge(*plot.GetDrawElements());
    linesToDraw.merge(*plot.GetSeriesLines());
}

void WaveViewer::Launch(int fpslim)
{
    sf::RenderWindow win(sf::VideoMode(config.xsize, config.ysize), config.winTitle, sf::Style::Default);

    // Framerate limiting
    if (fpslim > 0)
        win.setFramerateLimit(fpslim);

    // Create a font for window texts
    sf::Font font;
    std::string fontfolder = EnvTools::GetEnvVar(WV_VARENV_FONT_FOLDER);
    std::string fontname = WV_NAME_FONT_DEFAULT;
    font.loadFromFile(fontfolder + fontname);

    winInfoText = *(new sf::Text("---", font));
    winInfoText.setCharacterSize(15);

    // winInfoText.setStyle(sf::Text::Bold);
    winInfoText.setFillColor(sf::Color::Color::White);
    winInfoText.setPosition(0, 0);

    sf::CircleShape shape(100.0f);

    // Populate the drawing list
    toDraw.push_back(&winInfoText);

    // Fps timer
    auto guiloop_start{std::chrono::steady_clock::now()};
    auto guiloop_stop{std::chrono::steady_clock::now()};
    float fpsmean = 0;

    bool ui_update = true;

    int mouseX;
    int mouseY;

    while (win.isOpen())
    {
        guiloop_start = std::chrono::steady_clock::now();

        // Process events
        sf::Event Event;
        while (win.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                win.close();

            // Catch resize event
            if (Event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, Event.size.width, Event.size.height);
                win.setView(sf::View(visibleArea));
                // if the window changed size, ask for a redraw
                ui_update = true;
            }

            if (Event.type == sf::Event::MouseMoved)
            {
                // std::cout << "MouseX : " << Event.mouseMove.x << "MouseY : " << Event.mouseMove.y << std::endl;
                // mouseX = Event.mouseMove.x;
                // mouseY = Event.mouseMove.y;
            }
        }

        winSize = win.getSize();

        if (ui_update == true)
        {
            Redraw(win);
            ui_update = false;
        }

        guiloop_stop = std::chrono::steady_clock::now();

        // Compute fps
        std::chrono::duration<double> elapsed_seconds{guiloop_stop - guiloop_start};
        fpsmean = (fpsmean + 1 / elapsed_seconds.count()) / 2;

        winInfoText.setString("Render time : " + std::to_string(elapsed_seconds.count()) + "\n" + EnvTools::GetOsName() + " " + EnvTools::GetMachine());
    }
}

void WaveViewer::Redraw(sf::RenderWindow &win)
{
    sf::Color bg;
    bg.r = 27;
    bg.g = 30;
    bg.b = 31;
    bg.a = 255;

    // Clear the screen (fill it with black color)
    win.clear(bg);

    // Draw all objects in the draw list
    for (auto it = toDraw.begin(); it != toDraw.end(); ++it)
    {
        win.draw(**it);
    }

    // Draw all lines in the draw list
    for (auto it = linesToDraw.begin(); it != linesToDraw.end(); ++it)
    {
        win.draw(**it);
    }

    win.display();
}