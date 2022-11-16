//
// Created by Administrator on 2022/11/11.
//

#ifndef HTTPSERVER_PATH_H
#define HTTPSERVER_PATH_H

#include <string>
using std::string;

string basePath = "/tmp/System/json/";

string CfgPath = basePath + "system_cfg.json";
string fileAdressPath = basePath + "fileaddrs.json";
string keyValuePath = basePath + "keyvalue.json";

string loggerPath = basePath + "log/Httpserver.log";

string HttpServerFlag = basePath + "flag/http_server_flag";
string svpStatePath = basePath + "flag/svp_state";
string fnIdPath = basePath + "flag/fnId";

#endif //HTTPSERVER_PATH_H
