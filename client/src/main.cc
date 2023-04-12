#include"../include/head.h"
#include"../include/network.h"


int main(int argc, char *argv[])
{

    int port = 10240;
    std::string ip = "38.55.214.93";
    Network mynet(ip.c_str(),port);
    int sfd=mynet.initNetwork();


    int epfd = epoll_create(1);
    epoll_event event, evns[2];
    memset(&event, 0, sizeof(event));
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;

    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    event.data.fd = sfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &event);

    int readyNum = 0;
    while (1)
    {
        readyNum = epoll_wait(epfd, evns, 2, -1);
        for (int i = 0; i < readyNum; ++i)
        {
            if (evns[i].data.fd == STDIN_FILENO)
            {
                std::string line;
                getline(std::cin, line);
                // cout<<line<<endl;
                // cout<<line.size()<<std::endl;
                send(sfd, line.c_str(), line.size(), 0);
            }
            else if (evns[i].data.fd == sfd)
            {
                char buf[1024];
                memset(buf, '\0', 1024);
                int ret = recv(sfd, buf, sizeof(buf), 0);
                if(ret>0){cout << buf << endl;}
                else{
                    cout<<"wrong ret "<<ret<<endl;
                    close(sfd);
                    close(epfd);
                    return 0;
                }
            }
        }
    }
    close(sfd);
    close(epfd);
    return 0;
}