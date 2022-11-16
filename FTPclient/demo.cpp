//
// Created by Administrator on 2022/7/26.
//

#include <iostream>
#include <fstream>
#include "rjson.h"
#include "THFTPAPI.h"
#include <string>
#include "bcflag.h"
#include <unistd.h>
#include "magicLogger.h"
#include "FTPer.h"
#include "json.hpp"
#include "path.h"

using std::string;
using namespace nlohmann;
using namespace spdlog;



::magicLogger FtpLogger("FTP", loggerPath, 1024 * 1024 * 1, 1);
FTPer ftper;

string get_json_save_path(const char *ftype,const char *fname)
{
    string path;
    if (strcmp(ftype,"MODEL") == 0)
    {
        path = ftper.cfger.MODEL_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"PROGRAM") == 0)
    {
        path = ftper.cfger.PROGRAM_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"CONFIG") == 0)
    {
        path = ftper.cfger.CONFIG_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"PARAM") == 0)
    {
        path = ftper.cfger.PARAM_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"LIB") == 0)
    {
        path = ftper.cfger.LIB_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"START") == 0)
    {
        path = ftper.cfger.START_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"ZIP") == 0)
    {
        path = ftper.cfger.ZIP_path;
        path = path + fname;
        return path;
    }

}



int main(int argc,char** argv)
{
    if (argc != 2)
    {
        cout << "please input cfg path : /**/**/ " << endl;
        exit(1);
    }
    ftper.init(argv[1],FtpLogger.log);

    char* fpath[8];  //目标文件
    char* ftype[8];
    char* fname[8];
    char* json_save_path = new char[128];
    unsigned long long int filesize=0;


    while(1)
    {
        int get_path_flag = get_flag(HttpServerFlag.c_str());
        FtpLogger.log->debug("获取到 flag 值");
        if (get_path_flag == -1) continue;
        else if(get_path_flag == 1)
        {
            std::cout<< "获取到新路径" << std::endl;
            FtpLogger.log->debug("获取到新路径");
            unsigned long num = js_getfilepath(fpath,ftype,fname,fileAdressPath.c_str());
            int fnId = js_getfnId(fileAdressPath.c_str());
            set_flag(fnIdPath.c_str(),fnId);
            FtpLogger.log->info("get fnId:{}", get_flag(fnIdPath.c_str()));
            int socket = ftp_connect(ftper.cfger.HOST,ftper.cfger.PORT,ftper.cfger.USER,ftper.cfger.PWD);
            std::cout<< "-----------ftp_connected------------" << std::endl;
            FtpLogger.log->debug("-----------ftp_connected------------");
            for(int i = 0;i < num;i++ )
            {
                //s:目标文件位置
                //d:本地文件位置
                string savepath = get_json_save_path(ftype[i],fname[i]);
                std::cout<< "dest path: " << savepath << std::endl;
                FtpLogger.log->info("dest path: {}",savepath);
                strcpy(json_save_path,savepath.c_str());
                if (ftp_retrfile(socket, fpath[i], json_save_path ,&filesize, NULL)< -1)
                {
                    std::cout<< "read ftp file error,ftp path: " << fpath[i] << std::endl;
                    FtpLogger.log->info("read ftp file error,ftp path: {}",fpath[i]);
                    break;
                }
            }
            set_flag(HttpServerFlag.c_str(),"0");
            std::cout<< "success read size:" << filesize << std::endl;
            FtpLogger.log->info("success read size: {}",filesize);
            if (ftper.cfger.rebootFlag){
                std::cout<< "start reboot ...." << std::endl;
                FtpLogger.log->info("start reboot ....");
                system("reboot");
            }
        }
        sleep(2);
    }

    return 1;
}
