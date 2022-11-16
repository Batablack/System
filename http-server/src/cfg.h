//
// Created by Administrator on 2022/8/23.
//

#ifndef DOWNLOADWK_DEMO_CFG_H
#define DOWNLOADWK_DEMO_CFG_H

#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "spdlog/spdlog.h"
#include <cstdlib>  // exit()
#include "path.h"

using json = nlohmann::json;
using std::string;
using std::cout;
using std::endl;

using namespace spdlog;
extern string basePath;

enum deviceType{
    HI3516,
    TX2,
    PC
};

class HttpServerCfg{
public:
    HttpServerCfg(){URL = new char[128];}
    HttpServerCfg(string _cfgPath, std::shared_ptr<logger> _cfglog):
                    cfgPath(_cfgPath), cfglog(_cfglog){
        URL = new char[128];
        loadCfg();
        showCfg();
    }
    void init(const char * cfg_path,std::shared_ptr<logger> _cfglog);
    ~HttpServerCfg(){delete[] URL;}
    char *URL;
    bool loadCfg();
    bool showCfg();
    deviceType type;
private:
    std::shared_ptr<logger> cfglog;
    string cfgPath;
    json cfgJson;
    bool loadjson();
    void getDeviceType(string sType);
};

void HttpServerCfg::init(const char *cfg_path,std::shared_ptr<logger> _cfglog)
{
    cfgPath = cfg_path;
    cfglog = _cfglog;
    loadCfg();
    showCfg();

}


void HttpServerCfg::getDeviceType(std::string sType) {
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

bool HttpServerCfg::loadjson()
{
    std::ifstream i(cfgPath);
    if (!i.good()){
        cout << "Please input file: " << cfgPath << endl;
        cfglog->error("Please input file: {}",cfgPath);
        exit(EXIT_FAILURE);
        return false;
    }
    i >> cfgJson;
    return true;
}

bool HttpServerCfg::loadCfg()
{
    cout << "loadcfg ..." << endl;
    loadjson();
    string sType;
    sType = cfgJson.at("device_type");
    getDeviceType(sType);
    basePath = cfgJson.at("system_path");
    json httpcfg = cfgJson.at("HttpServer_cfg");
    string tmp;
    tmp = httpcfg.at("url");
    strcpy(URL,tmp.c_str());
    cout << "loadcfg DONE"<<endl;
}
bool HttpServerCfg::showCfg()
{
    cfglog->info("==== get config ====");
    cfglog->info("url:{}",URL);
    cfglog->info("base_path:{}",basePath);
    cfglog->info("====================");
    return true;
}


#endif //DOWNLOADWK_DEMO_CFG_H
