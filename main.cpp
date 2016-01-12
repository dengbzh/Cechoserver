/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/10/2016 06:05:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"Socket.h"

class Echoserver:public Socket
{
public:
    Echoserver(const char*ip,int port,int backlog):Socket(ip,port,backlog){}
    void task(int clinetfd)
    {
        ssize_t rev;
        while((rev = recv(clinetfd,buf,BUFFERSIZE-1,0)) > 0)
        {
            if(send(clinetfd,buf,rev,0) < 0)
            {
                err_sys("server send back error...\n");
            }
        }
        printf("servece closed...\n");
        close(clinetfd);
    }
};

int main(int argc,char *argv[])
{
 
    if(argc <= 2)
    {
        err_msg("too liiter parameters...\n");
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);
    /* 
    const char *ip = "127.0.0.1";
    int port = 6666;
    int backlog = 5;
     
    int socketfd = socket(PF_INET,SOCK_STREAM,0);
    struct sockaddr_in address;
    bzero(&address,sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&address.sin_addr);
    address.sin_port = htons(port);

    int ret = bind(socketfd,(struct sockaddr*)&address,sizeof(address));
    */
    Echoserver *server = new Echoserver(ip,port,backlog);    
    server->Server(); 
    delete server;
    return 0;
}
