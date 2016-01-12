/*
 * =====================================================================================
 *
 *       Filename:  Socket.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/10/2016 05:12:08 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dengbzh (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef _SOCKET_H
#define _SOCKET_H
#include"Utility.h"
#define BUFFERSIZE 1024
class Socket{
private:
    Socket();
    int m_socketfd;
    int m_clientfd;
    int m_port;
    int m_backlog;
    const char *m_ip;
    struct sockaddr_in m_address;
    struct sockaddr_in m_client;
public:
    Socket(const char *ip,int port,int backlog);
    virtual ~Socket();
    void Server();
    void closeServerfd(){close(m_socketfd);}
    void closeClientfd(){close(m_clientfd);}
    virtual void task(int clientfd) = 0;
    void runSev(){task(m_clientfd);}
    char buf[BUFFERSIZE];

};


#endif
