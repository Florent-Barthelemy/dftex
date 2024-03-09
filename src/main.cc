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




int main(void)
{   
    std::cout << "Running on  : " << EnvTools::GetOsName() << " " << EnvTools::GetMachine() << std::endl;
    std::cout << "Checking WV : " << EnvTools::GetEnvVar(WV_VARENV_FONT_FOLDER) << std::endl;
    WaveViewerConfig wcfg;
    wcfg.winTitle = "Wave 0";
    wcfg.xsize = 400;
    wcfg.ysize = 400;

    // DiscreteTime dtime(0*UNIT_MS, 5*UNIT_MS);
    DiscreteTime dtime(-10*UNIT_MS, 10*UNIT_MS);
    dtime.Sample(1*UNIT_MHZ); // 1kHz sampling (1ms Te)

    std::vector<double> sinewave;
    std::vector<double> editedTime;

    for(int i = 0; i < dtime.GetVector()->size(); i++)
    {
        double xval = 2*M_PI*1*UNIT_KHZ*dtime.GetVector()->at(i);
        //double sinc = sqrt(pow(sin(xval)/xval, 2));
        double sinc = sin(xval)/xval;

        //Sinc def.
        if(xval  == 0)
            sinc = 1;
        
        editedTime.push_back(xval);
        sinewave.push_back(sinc);
    }

    std::vector<double> sinewave2;
    std::vector<double> editedTime2;

    for(int i = 0; i < dtime.GetVector()->size(); i++)
    {
        double xval = 2*M_PI*10*UNIT_KHZ*dtime.GetVector()->at(i);
        //double sinc = sqrt(pow(sin(xval)/xval, 2));
        double sinc = cos(xval);
        
        //Sinc def.
        if(xval  == 0)
            sinc = 1;
        
        editedTime2.push_back(xval);
        sinewave2.push_back(sinc);
    }

    PlotPane wave0(50, 50, 300, 300, 20, 20);


    wave0.AddSeries(&editedTime, &sinewave, editedTime.size(), sf::Color::Blue);

    WaveViewer wv(wcfg);
    wv.AddPlotPane(wave0);




    wv.Launch(41);

   

    

    // 
}