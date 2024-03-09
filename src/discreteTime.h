#ifndef TIME_H
#define TIME_H

#include <vector>

class DiscreteTime
{
    public:
        /// @brief Creates a resample-able discrete time vector to base signals on
        /// @param start
        /// @param stop
        DiscreteTime(double start, double stop);

        /// @brief Samples the time with the apropriate frequency
        /// @param sampling_freq 
        /// @return Number of time samples
        long long int Sample(double sampling_freq);

        std::vector<double>* GetVector();

    private:
        std::vector<double> sampledTime;
        double sampling_freq;
        double start_time;
        double stop_time;    
};

#endif