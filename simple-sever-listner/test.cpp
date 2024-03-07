#include "server.h"
#include <signal.h>
#include<iostream>
// std::function<void(void)> f;

// void regist(int)
// {
//     std::cout<<"Interrrupt received"<<std::endl;
//     f();
// }

// void register_interrupt()
// {
//     signal(SIGINT,regist);
//     signal(SIGTERM,regist);
// }

int main(int argc, char *argv[]) {

  auto myServer = Server();
//   f=std::bind(&Server::closeSockSignal, &myServer);
//   register_interrupt();
  myServer.start();

  return 0;
}