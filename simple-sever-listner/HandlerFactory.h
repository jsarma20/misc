#include<stdexcept>
#include "IHandler.h"
#include "EchoHandler.h"


#ifndef HANDLER_FACTORY_H
#define HANDLER_FACTORY_H

class NotImplemented : public std::logic_error
{
  public:
  NotImplemented():std::logic_error("Not implemented Exception"){}
};

enum Handle
{
  Echo,
  Callback
};


class HandlerFactory
{
  public:
  IHandler* getHandler(int type)
  {
    switch(type)
    {
      case Handle::Echo:
      return new ReadHandler();
      break;
      case Handle::Callback:
      throw NotImplemented();
      break;
      default:
      throw std::runtime_error("Unknown handler");
    }
  }
};

#endif