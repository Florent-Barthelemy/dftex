#include "discreteTime.h"

DiscreteTime::DiscreteTime(double start_ms, double stop_ms)
{
    this->start_time = start_ms;
    this->stop_time = stop_ms;
}

long long int DiscreteTime::Sample(double sampling_freq)
{
    std::vector<double> spt;
    long long int points = (stop_time - start_time)*sampling_freq;
    double timestep_ms = 1/sampling_freq;
    
    double currentTime_ms = start_time;

    for(long long int i = 0; i < points; i++)
    {
        spt.push_back(currentTime_ms);
        currentTime_ms += timestep_ms;
    }

    //Push the time limit value to the samples
    spt.push_back(currentTime_ms);

    this->sampledTime = spt;

    return points;
}

std::vector<double>* DiscreteTime::GetVector()
{
    return &this->sampledTime;
}