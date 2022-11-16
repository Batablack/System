//
// Created by Administrator on 2022/11/11.
//

#ifndef FTPCLIENT_FTPER_H
#define FTPCLIENT_FTPER_H

#include "FTPcfg.h"

class FTPer
{
    friend class FtpCfg;
public:
    FTPer(){}
    FTPer(string _cfgPath, std::shared_ptr<logger> _ftplog):
            CfgPath(_cfgPath), ftplog(_ftplog){

    }
    void init(const char * _cfgPath, std::shared_ptr<logger> _ftplog);
    FtpCfg cfger;
private:
    string CfgPath;
    std::shared_ptr<logger> ftplog;
};

void FTPer::init(const char * _cfgPath, std::shared_ptr<logger> _ftplog)
{
    CfgPath = _cfgPath;
    ftplog = _ftplog;
    cfger.initCfg(_cfgPath,_ftplog);
}

#endif //FTPCLIENT_FTPER_H
