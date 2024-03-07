#include<iostream>

#ifndef SIMPLE_LOGGER
#define SIMPLE_LOGGER

namespace logging
{

enum Log
{
    info     = 0,
    warn     = 1,
    critical = 2,
    error    = 3
};
extern const std::string LOG_LEVEL[];
void log(std::string , logging::Log);
}
#endif
