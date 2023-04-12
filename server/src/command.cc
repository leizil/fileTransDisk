#include "../include/head.h"
#include "../include/command.h"

std::set<std::string> shortCommand{"cd", "ls", "pwd", "mkdir"};

Command::Command()
    : _curCommand(""), _curPath("/home/llz/log")

{
    // std::cout << "Command::Command()" << std::endl;
    chdir(_curPath.c_str());
}

Command::~Command()
{
    // std::cout << "Command::~Command()" << std::endl;
}

int Command::myLs(std::string dst) // ls
{
    // int rst = chdir(dst.c_str());
    // _curPath=getcwd(NULL,0);
    DIR *pdir = opendir(dst.c_str());
    // ERROR_CHECK("opendir",0);
    if (pdir == nullptr)
    {
        std::cout << "opendir error" << std::endl;
        return 0;
    }
    dirent *pdirent;
    char buf[1024];
    while ((pdirent = readdir(pdir)))
    {
        if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
        {
            continue;
        }
        // std::cout << pdirent->d_name << std::endl;
        _rst=_rst+pdirent->d_name+"\n";
    }
    closedir(pdir);
    return 0;
}


int Command::myLs() // ls
{
    // _curPath=myGetcwd();
    // int rst = chdir(dst.c_str());
    // _curPath=getcwd(NULL,0);
    DIR *pdir = opendir(_curPath.c_str());
    std::cout<<"myLs()  _curpath: "<<_curPath<<std::endl;
    // ERROR_CHECK("opendir",0);
    if (pdir == nullptr)
    {
        std::cout << "opendir error" << std::endl;
        return 0;
    }
    dirent *pdirent;
    char buf[1024];
    while ((pdirent = readdir(pdir)))
    {
        if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
        {
            continue;
        }
        // std::cout << pdirent->d_name << std::endl;
        _rst=_rst+pdirent->d_name + "\n"; 
    }
    closedir(pdir);
    return 0;
}


int Command::myRm(std::string filename)
{
    std::string dst=_curPath+"/"+filename;
    struct stat buf;
    stat(dst.c_str(),&buf);
    if(S_ISDIR(buf.st_mode)){
        _rst="can not remove,is a dir ";
    }else{
        std::cout<<dst<<std::endl;
        int ret=remove(dst.c_str());
        if(ret<1){

        }
    }
    return 0;
} //rm


int Command:: getsFile(std::string filename)
{
    return 0;
} //下载


int Command::putsFile(std::string filename){
    return 0;
} //上传

const char *Command::myGetcwd() // cwd
{
    std::string buf;
    // buf = getcwd(NULL, 0);
    buf=_curPath;
    // std::cout << buf << std::endl;
    _rst=buf;
    _curPath=buf;
    return buf.c_str();
}

int Command::myChdir(std::string dst) // cd
{
    int rst = chdir(dst.c_str());
    _curPath=getcwd(NULL,0);
    return rst;
}

int Command::myMkdir(std::string dst)
{
    int rst = mkdir(dst.c_str(), S_IRWXU | S_IRWXO | S_IRWXG);
    return rst;
}

int Command::parseCommand(const char *pstr)
{
    _rst.clear();
    std::istringstream iss(pstr);
    std::string temp;
    while (iss >> temp)
    {
        _param.push_back(temp);
    }
    // std::cout<<"_param size "<<_param.size()<<std::endl;
    return 0;
}

// std::vector<std::string> Command::clearRst()
// {
//     std::vector<std::string>().swap(_rst);
//     return _rst;
// }

std::string Command::execCommand()
{
    _rst="";
    
    if (_param[0] == "pwd")
    {
        myGetcwd();
        // std::cout << myGetcwd() << std::endl;
        // std::cout << "_rst size: "<<_rst.size() << std::endl;
    }
    else if (_param[0] == "cd")
    {
        myChdir(_param[1]);
        // _rst=clearRst();
        // std::cout << "_rst size: "<<_rst.size() << std::endl;
    }
    else if (_param[0] == "rm")
    {
        myRm(_param[1]);
        // _rst=clearRst();
        // std::cout << "_rst size: "<<_rst.size() << std::endl;
    }
    else if (_param[0] == "ls")
    {
        // _rst=clearRst();
        // std::cout << "_rst size: "<<_rst.size() << std::endl;
        if(_param.size()>1){
             myLs(_param[1].c_str());
        }else{
            myLs();
        }
       
    }
    else if (_param[0] == "mkdir")
    {

        myMkdir(_param[1].c_str());
        // _rst=clearRst();
    }
    else
    {
        // std::cout << "wrong command, please input correct command!" << std::endl;
        // clearRst();
        _rst="wrong command, please input correct command!"  ;  
    }
    _param.clear();
    // for(auto&elem:_rst){
    //     _to_client+=elem+"\n";
    // }
    // std::cout << "to_client : "<<_rst << std::endl;
    return _rst;
}

// Command* Command::_pInstance=new Command();
// Command::destroy Command::_destroy;

// int main()
// {
//     Command* c1=Command::getInstance();
//     Command* c2=Command::getInstance();
//     while(1){
//         std::string line;
//         getline(std::cin,line);
//         c1->parseCommand(line.c_str());
//         c1->execCommand();
//     }
    

//     return 0;
// }