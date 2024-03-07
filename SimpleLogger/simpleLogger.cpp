#include <string>
#include "simpleLogger.h"
const std::string logging::LOG_LEVEL[] = 
{
"INFO",
"WARN",
"CRITICAL",
"ERROR"
};

void logging::log(std::string msg, logging::Log level=logging::info)
{
#ifndef NO_LOG
std::cout<<LOG_LEVEL[level]<<":"<<msg<<std::endl;
#endif
}