#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include<vector>

class Command
{

private:
    class destroy
    {
    private:
        /* data */
    public:
        ~destroy()
        {
            if (_pInstance)
            {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

public:
    static Command *getInstance()
    {
        if (_pInstance == nullptr)
        {
            _pInstance = new Command();
        }
        return _pInstance;
    }
    int parseCommand(const char* pstr);
    std::string execCommand();
    ~Command();
    // std::vector<std::string> clearRst();

private:
    int myLs(std::string dst) ;       // ls
    int myLs() ;   
    const char *myGetcwd();            // cwd
    int myChdir(std::string dst);      // cd
    int myMkdir(std::string dst); // mkdir
    int myRm(std::string dst); //rm
    int getsFile(std::string filename); //下载
    int putsFile(std::string filename); //上传

private:
    /* data */
    std::string _curPath;
    std::string _curCommand;
    std::vector<std::string> _param;
    static Command *_pInstance;
    std::string _to_client;
    std::string _rst;
    Command();
    static destroy _destroy;
    
};



#endif