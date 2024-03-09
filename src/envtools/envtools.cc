#include "envtools.h"


/// @brief Returns Operating system name
/// @return 
std::string EnvTools::GetOsName()
{
    //From IBM Docs
    struct utsname uts;
    if(uname(&uts) < 0)
        return "Fail";
    else
        return uts.sysname;
}

/// @brief Returns machine type (x86, etc)
/// @return 
std::string EnvTools::GetMachine()
{
    //From IBM Docs
    struct utsname uts;
    if(uname(&uts) < 0)
        return "Fail";
    else
        return uts.machine;
}

/// @brief Returns an environnement variable value
/// @return 
std::string EnvTools::GetEnvVar(const char* varname)
{
    if(const char* env_p = std::getenv(varname))
        return env_p;
    else
        return "Fail";
}

