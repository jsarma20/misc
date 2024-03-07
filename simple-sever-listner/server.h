#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // for close
#include <string.h>
#include <list>
#include "IHandler.h"
#include "HandlerFactory.h"
#include "ThreadPool.h"

#ifndef SERVER_H
#define SERVER_H

constexpr int MAX_BACKLOG = 10;
constexpr int DEFAULT_PORT = 8003;

class IServer
{
  public:
  IServer(int port, int mbacklog=MAX_BACKLOG):max_backlog(mbacklog),listnerPort(port){}

  protected:
  int max_backlog; // maximum allowed new connections
  int listnerPort;

  
};

class Server : public IServer
{
  public:
  Server(int maxConnections=MAX_BACKLOG, int port=DEFAULT_PORT,Handle type = Handle::Echo )
  :IServer(port,maxConnections), handler_type(type)
  {
    listners = std::make_shared<ThreadPool<int>>();
    handler_factory = HandlerFactory();
  }

  int start();
  ~Server()
  {
    close(server_sockfd);
  }

  void closeSockSignal()
  {
    close(server_sockfd);
  }

  private:           
  int server_sockfd;      // server socket fd listen for new connections
  Handle handler_type;
  std::shared_ptr<ThreadPool<int>> listners;
  HandlerFactory handler_factory;
};

#endif
