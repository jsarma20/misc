#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "IHandler.h"
#include "simpleLogger.h"
#include<thread>
#include <sstream>
#ifndef ECHO_HANDLER_H
#define ECHO_HANDLER_H


class ReadHandler : public IHandler
{
  public:
  ReadHandler(){}

  int handle() override
  {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    std::string id = ss.str();
    log(std::string("Echo handler!"+id + " on sock "+ std::to_string(this->listner_sock)), logging::info);
    
    return echo();
    
  }

  int echo()
  {

    std::shared_ptr<char[]> rmessage;
    while(readBytes(rmessage))
    {
      std::string s(rmessage.get());
      std::cout<<"received message "<<s<<std::endl;
      rmessage.reset();
    }

    return 1;
  }
  ~ReadHandler(){}

  protected:
  int readBytes(std::shared_ptr<char[]>& buf)
  {
    std::shared_ptr<char[]> buff(new char[READ_BUFF_SIZE]);
    memset(buff.get(),'\0',READ_BUFF_SIZE);
    int rec = recv(listner_sock, buff.get(), READ_BUFF_SIZE, 0);
    if(rec>0)
    {

      buf=buff;
      return 1;
    }
    return 0;
  }

  private:
  static const size_t READ_BUFF_SIZE = 4096;
};

#endif