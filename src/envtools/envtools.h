#ifndef ENVTOOLS_H
#define ENVTOOLS_H

#include <string>
#include <cstdlib>
#include <sys/utsname.h>


/// @brief Provides a set of static utility methods for environnement variables access & other
class EnvTools
{
    public:
        static std::string GetOsName();
        static std::string GetMachine();
        static std::string GetEnvVar(const char*);
};

#endif