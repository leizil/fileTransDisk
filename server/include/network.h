#ifndef __NETWORK_H__
#define __NETWORK_H__

#include"./head.h"


class Network
{
private:
    /* data */
    int _sfd;
    int _status;
    int _port;
    std::string _ip;
    sockaddr_in _serverAddr;
public:
    Network();
    Network(const char* ptr,int port);
    int initNetwork();
    int waitWorking();
    ~Network();
    void ERROR_CHECK(int wrong_number,const char*ptr);
    void ERROR_CHECK(int rst,int wrong_number,const char*ptr);
};








#endif