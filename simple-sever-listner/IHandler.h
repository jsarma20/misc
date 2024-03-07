#include <unistd.h> // for close
#ifndef IHANDLER_H
#define IHANDLER_H
#include<iostream>
#include <sstream>
class IServer;

class IHandler
{
  public:
  IHandler(){}
  virtual int handle()=0;
  void setSocket(int sockfd){listner_sock=sockfd;}
  
  virtual ~IHandler()
  {
    std::stringstream ss;
    ss << std::this_thread::get_id();
    std::string id = ss.str();
    
    std::cout<<"closing sock:"<<listner_sock<<"from thread "<<id<<std::endl;
    close(listner_sock);
  }

  protected:
  int listner_sock;
};

#endif