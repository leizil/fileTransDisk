#include"../include/network.h"



Network::Network()
:_ip("")
,_port(0)
,_status(0)
{
    memset(&_clientAddr,0,sizeof(_clientAddr));
}

int Network::initNetwork()
{
    _sfd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(_sfd,-1,"socket");
    
    _clientAddr.sin_family=AF_INET;
    _clientAddr.sin_port=htons(_port);
    _clientAddr.sin_addr.s_addr=inet_addr(_ip.c_str());

    // _status=bind(_sfd,(sockaddr*)&_serverAddr,sizeof(sockaddr));

    // _status=listen(_sfd,5);
    _status=connect(_sfd, (sockaddr *)&_clientAddr, sizeof(sockaddr));
    ERROR_CHECK(-1,"connect");
    return _sfd;
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

// int Network::waitWorking()
// {
//     socklen_t addrlen=sizeof(sockaddr);
//     int newsfd=accept(_sfd,(sockaddr*)&_serverAddr,&addrlen);
//     if(newsfd<0){
//         std::cout<<"connected?"<<std::endl;
//     }else{
//         std::cout<<"connected!!!!!"<<std::endl;
//     }
//     return newsfd;
// }


Network::Network(const char* ptr,int port)
:_ip(ptr)
,_port(port)
{

}


Network::~Network()
{
    if(!_sfd)
    {
        close(_sfd);
    }
}