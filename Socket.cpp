/*
 * =====================================================================================
 *
 *       Filename:  Socket.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/10/2016 05:12:24 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include"Socket.h"

Socket::Socket(const char *ip,int port,int backlog)
{
    m_ip = ip;
    m_port = port;
    m_backlog = backlog;
    bzero(&m_address,sizeof(m_address));
    m_address.sin_family = AF_INET;
    inet_pton(AF_INET,m_ip,&m_address.sin_addr);
    m_address.sin_port = htons(m_port);
}
Socket::~Socket()
{
    closeServerfd();    
}
void Socket::Server()
{
    m_socketfd = socket(PF_INET,SOCK_STREAM,0);
    if(m_socketfd < 0)
    {
        err_sys("socket create failed...\n");
    }
 
    int ret = bind(m_socketfd,(struct sockaddr*)&m_address,sizeof(m_address));
    if(ret == -1)
    {
        err_sys("bind failed...\n");
    }
    ret = listen(m_socketfd,m_backlog);
    if(ret == -1)
    {
        err_sys("listen failed...\n");
    }
    socklen_t client_addrlen = sizeof(m_client);
    m_clientfd = accept(m_socketfd,(struct sockaddr*)&m_client,&client_addrlen);
    if(m_clientfd < -1)
    {
        err_sys("server accept failed...\n");
    }
    printf("Run task...\n");
    runSev();
}
/* 
void Socket::Client()
{
    if(connect(m_socketfd,(struct sockaddr*)&m_address,sizeof(m_address)) < 0)
    {
        err_sys("client connect failed..\n");
    }
    else
    {
        task(m_socketfd);
    }
    close(m_socketfd);
}
*/
