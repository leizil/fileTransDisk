#include"../include/network.h"



Network::Network()
:_ip("")
,_port(0)
,_status(0)
{
    memset(&_serverAddr,0,sizeof(_serverAddr));
}

void Network::ERROR_CHECK(int wrong_number,const char*ptr)
{
    if(_status==wrong_number)
    {
        std::cout<<ptr<<" error"<<std::endl;
    }
}

void Network::ERROR_CHECK(int rst,int wrong_number,const char*ptr)
{
    if(rst==wrong_number)
    {
        std::cout<<ptr<<" error"<<std::endl;
    }
}

int Network::initNetwork()
{
    _sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(_sfd,-1,"socket");
    
    _serverAddr.sin_family=AF_INET;
    _serverAddr.sin_port=htons(_port);
    _serverAddr.sin_addr.s_addr=inet_addr(_ip.c_str());

    _status=bind(_sfd,(sockaddr*)&_serverAddr,sizeof(sockaddr));
    ERROR_CHECK(-1,"bind");
    _status=listen(_sfd,5);
    ERROR_CHECK(-1,"listen");

    return _sfd;
}


int Network::waitWorking()
{
    socklen_t addrlen=sizeof(sockaddr);
    int newsfd=accept(_sfd,(sockaddr*)&_serverAddr,&addrlen);
    if(newsfd<0){
        ERROR_CHECK(newsfd,-1,"accept");
        ERROR_CHECK(newsfd,0,"accept");
    }else{
        std::cout<<"connected!!!!!"<<std::endl;
    }
    return newsfd;
}


Network::Network(const char* ptr,int port)
:_ip(ptr)
,_port(port)
{

}


Network::~Network()
{
    
    
    close(_sfd);
    
}