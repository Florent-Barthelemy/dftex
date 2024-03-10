#include <iostream>
#include <math.h>
#include "signal.h"
#include "discreteTime.h"
#include "units.h"
#include "waveview/waveview.h"
#include "waveview/plotpane.h"
#include "envtools/envtools.h"
#include "softenv.h"

#include <SFML/Graphics.hpp>


void TestWaveView()
{
    std::cout << "Running on  : " << EnvTools::GetOsName() << " " << EnvTools::GetMachine() << std::endl;
    std::cout << "Checking WV : " << EnvTools::GetEnvVar(WV_VARENV_FONT_FOLDER) << std::endl;
    WaveViewerConfig wcfg;
    wcfg.winTitle = "Dftex WaveView";
    wcfg.xsize = 1100;
    wcfg.ysize = 600;

    // DiscreteTime dtime(0*UNIT_MS, 5*UNIT_MS);
    DiscreteTime dtime(-1*UNIT_MS, 1*UNIT_MS);
    dtime.Sample(1000*UNIT_KHZ); // 1kHz sampling (1ms Te)

    std::vector<double> sinewave;
    std::vector<double> editedTime;

    double sinc = 0;
    for(int i = 0; i < dtime.GetVector()->size(); i++)
    {
        double xval = 2*M_PI*0.5*UNIT_KHZ*dtime.GetVector()->at(i);
        //double sinc = sqrt(pow(sin(xval)/xval, 2));
        sinc = 2*sin(xval);

        //Sinc def.
        //if(xval  == 0)
          //  sinc = 1;
        
        editedTime.push_back(xval);
        sinewave.push_back(sinc);
    }

    std::vector<double> sinewave2;
    std::vector<double> editedTime2;

    sinc = 0;
    for(int i = 0; i < dtime.GetVector()->size(); i++)
    {
        double xval = 2*M_PI*10*UNIT_KHZ*dtime.GetVector()->at(i);
        //double sinc = sqrt(pow(sin(xval)/xval, 2));
        sinc = sin(xval);

        //Sinc def.
        //if(xval  == 0)
          //  sinc = 1;
        
        editedTime2.push_back(xval);
        sinewave2.push_back(sinc);
    }


    //PANE 1
    PlotPaneTitle title{"Reference : sin(x)@10kHz, Blue : 2*sin(x)@500Hz", 0, 0, 15};
    PlotPane wave0(50, 50, 1000, 200, 25, 2, 3, title);
    wave0.SetXYReferenceSerie(&editedTime, &sinewave2, editedTime.size());

    int geometries = wave0.AddSeries(&editedTime, &sinewave, editedTime.size(), sf::Color::Blue);
    geometries = wave0.AddSeries(&editedTime, &sinewave2, editedTime2.size(), sf::Color::Red);

    //PANE 2
    PlotPaneTitle title1{"Reference : 2*sin(x)@500Hz, Red : sin(x)@10kHz", 0, 0, 15};
    PlotPane wave1(50, 300, 1000, 200, 25, 2, 3, title1);
    wave1.SetXYReferenceSerie(&editedTime, &sinewave, editedTime.size());

    geometries += wave1.AddSeries(&editedTime, &sinewave, editedTime.size(), sf::Color::Blue);
    geometries += wave1.AddSeries(&editedTime, &sinewave2, editedTime2.size(), sf::Color::Red);

    std::cout << "Rendered plot geometries per frame : " << geometries << " -> " << 100*geometries/(wcfg.xsize*wcfg.ysize) << "% filling" << std::endl;
    WaveViewer wv(wcfg);
    wv.AddPlotPane(wave0);
    wv.AddPlotPane(wave1);
    
    wv.Launch(41); 
}

int main(void)
{   
    TestWaveView();
}

