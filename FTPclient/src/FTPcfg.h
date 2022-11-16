//
// Created by Administrator on 2022/8/23.
//

#ifndef DEMO_DEMO_H
#define DEMO_DEMO_H

#include <string>
#include "spdlog/spdlog.h"
#include <cstdlib>  // exit()
#include <iostream>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using std::string;
using namespace spdlog;
using std::cout;
using std::endl;

extern string basePath;

enum deviceType{
    HI3516,
    TX2,
    PC
};


class FtpCfg {
public:
    FtpCfg() {
        HOST = new char[128];
        USER = new char[128];
        PWD = new char[128];
    }

    FtpCfg(string _cfgPath, std::shared_ptr<logger> _cfglog) :
            cfgPath(_cfgPath), cfglog(_cfglog) {
        HOST = new char[128];
        USER = new char[128];
        PWD = new char[128];
        loadCfg();
        showCfg();
    }

    ~FtpCfg() {
        delete[] HOST;
        delete[] USER;
        delete[] PWD;
    }

    void initCfg(const char * _cfgPath, std::shared_ptr<logger> &_cfglog);

    char *HOST;
    int PORT;
    char *USER;
    char *PWD;
    int rebootFlag;
    string MODEL_path;
    string PROGRAM_path;
    string CONFIG_path;
    string PARAM_path;
    string LIB_path;
    string START_path;
    string ZIP_path;
    deviceType type;
private:
    void getDeviceType(std::string sType);
    bool loadCfg();

    bool showCfg();

    string cfgPath;

    bool loadjson();

    std::shared_ptr<logger> cfglog;
    json cfgJson;


};

void FtpCfg::getDeviceType(std::string sType) {
    if (sType == "HI3516") type = HI3516;
    else if(sType == "TX2") type = TX2;
    else if(sType == "PC") type = TX2;
    else {
        cout << "Device Type Error!" << endl;
        cout << "please check system_cfg.json" << endl;
        cout << "you can use  HI3516, TX2, PC " << endl;
        exit(1);
    }
}

void FtpCfg::initCfg(const char * _cfgPath, std::shared_ptr<logger> &_cfglog) {
    cfgPath = _cfgPath;
    cfglog = _cfglog;
    loadCfg();
    showCfg();
}

bool FtpCfg::loadjson() {
    std::ifstream i(cfgPath);
    if (!i.good()) {
        cout << "Please input file: " << cfgPath << endl;
        cfglog->error("Please input file: {}", cfgPath);
        exit(EXIT_FAILURE);
        return false;
    }
    i >> cfgJson;
    return true;
}

bool FtpCfg::loadCfg() {
    cout << "loadcfg ..." << endl;
    json j, ftpcfg;
    std::cout << "cfgPath : " << cfgPath << std::endl;
    loadjson();
    string sType = cfgJson.at("device_type");
    getDeviceType(sType);
    basePath = cfgJson.at("system_path");
    ftpcfg = cfgJson.at("ftp_cfg");
    string tmp;
    try {
        tmp = ftpcfg.at("host");
        strcpy(HOST, tmp.c_str());
        tmp = ftpcfg.at("user");
        strcpy(USER, tmp.c_str());
        tmp = ftpcfg.at("pwd");
        strcpy(PWD, tmp.c_str());

        PORT = ftpcfg.at("port");
        rebootFlag = ftpcfg.at("reboot");
        MODEL_path = ftpcfg.at("MODEL_path");
        PROGRAM_path = ftpcfg.at("PROGRAM_path");
        CONFIG_path = ftpcfg.at("CONFIG_path");
        PARAM_path = ftpcfg.at("PARAM_path");
        LIB_path = ftpcfg.at("LIB_path");
        START_path = ftpcfg.at("START_path");
        ZIP_path = ftpcfg.at("ZIP_path");
    }
    catch (json::type_error &e) {
        std::cout << e.what() << '\n';
        cfglog->error("json error: {}", e.what());
        exit(EXIT_FAILURE);
    }

    cout << "FTP CFG DONE" << endl;
}

bool FtpCfg::showCfg() {
    cfglog->info("host:{}", HOST);
    cfglog->info("PORT:{}", PORT);
    cfglog->info("user:{}", USER);
    cfglog->info("pwd:{}", PWD);
    cfglog->info("reboot:{}", rebootFlag);
    cfglog->info("MODEL_path:{}", MODEL_path);
    cfglog->info("PROGRAM_path:{}", PROGRAM_path);
    cfglog->info("CONFIG_path:{}", CONFIG_path);
    cfglog->info("PARAM_path:{}", PARAM_path);
    cfglog->info("LIB_path:{}", LIB_path);
    cfglog->info("START_path:{}", START_path);
    cfglog->info("ZIP_path:{}", ZIP_path);
    return true;
}

#endif //DEMO_DEMO_H
