//
// Created by Administrator on 2022/7/27.
//

#ifndef FTPCLIENT_RJSON_H
#define FTPCLIENT_RJSON_H
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>


unsigned long js_getfilepath(char ** file_path,char ** file_type,char ** file_name,const char * json_path);
int js_getfnId(const char * json_path);
#endif //FTPCLIENT_RJSON_H
