#include "../include/head.h"
#include "../include/network.h"
#include "../include/command.h"

using std::cout;
using std::endl;

Command *Command::_pInstance = new Command();
Command::destroy Command::_destroy;


int ERROR_CHECK(int rst,int key,const char* ptr)
{
    if(key==rst){
        cout<<ptr<<" error "<<endl;
    }
}


int main(int argc, char *argv[])
{
    int epfd = epoll_create(1);
    ERROR_CHECK(epfd,-1,"epoll_create");
    
    int port = 10240;
    std::string ip = "38.55.214.93";

    Network serverNet(ip.c_str(), port);

    int sfd = serverNet.initNetwork();
    int newsfd = serverNet.waitWorking();

    epoll_event event, events[2];
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = newsfd;

    epoll_ctl(epfd, EPOLL_CTL_ADD, newsfd, &event);

    event.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);

    int readyNum = 0;
    while (1)
    {
        readyNum = epoll_wait(epfd, events, 2, -1);
        for (int i = 0; i < readyNum; ++i)
        {
            if (events[i].data.fd == newsfd)
            {
                Command *c1 = Command::getInstance();
                char buf[1024];
                memset(buf, 0, 1024);
                int ret = recv(newsfd, buf, sizeof(buf), 0);

                cout << buf << endl;

                c1->parseCommand(buf);
                auto rst = c1->execCommand();
                // cout << "server rst to_client " << rst << endl;

                send(newsfd, rst.c_str(), rst.size(), 0);

                if (ret == 0)
                {
                    cout << "client closed" << endl;
                    close(sfd);
                    close(newsfd);
                    close(epfd);
                    return 0;
                }
            }
        }
    }

    close(newsfd);
    close(sfd);
    close(epfd);
    return 0;
}
