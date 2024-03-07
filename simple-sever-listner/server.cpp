#include "server.h"

int Server::start()
{
    listners->run(3);
    struct sockaddr_in server_addr;     // server info struct
    server_addr.sin_family=AF_INET;     // TCP/IP
    server_addr.sin_addr.s_addr=INADDR_ANY;     // server addr--permit all connection
    server_addr.sin_port=htons(listnerPort);       // server port

    if((server_sockfd=socket(PF_INET,SOCK_STREAM,0))<0) {  
                    perror("socket error");
                    return 1;
    }

    if(bind(server_sockfd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr))<0) {
                    perror("bind error");
                    return 1;
    }
    if(listen(server_sockfd,max_backlog)<0) {
                    perror("listen error");
                    return 1;
    }
    printf("listen success.\n");

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

        int conn = accept(server_sockfd, (struct sockaddr*)&client_addr,&length);
        if(conn<0) {
            perror("connect");
            return -1;
        }

    

        char client_ip[INET_ADDRSTRLEN] = "";
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        printf("new client accepted. client(%s:%d)\n",client_ip,client_addr.sin_port);
        
        std::shared_ptr<IHandler> handler(handler_factory.getHandler(0));
        handler->setSocket(conn);
        std::function<int(void)>f = std::bind(&IHandler::handle, handler);
        listners->addTask(std::move(f));
    }

}