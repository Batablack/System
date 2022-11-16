//
// Created by Administrator on 2022/7/27.
//

#include "rjson.h"
using namespace nlohmann;
using namespace std;



int js_getfnId(const char * json_path)
{
    json j;
    unsigned long num;
    std::ifstream i(json_path);
    i >> j;
    json fjson = j.at("modelFileArray")[0];
    //get file path
    return fjson.at("fnId");
}

/*
 * js_getfilepath(char * file_path,char * json_path)
 * 获取多条路径信息
 * 输入&返回：file_path: 二维数组，记录多条路径的路径信息
 * 输入：json_path：json文件地址
 * return ：路径个数   -1：错误
 *
 * */
unsigned long js_getfilepath(char ** file_path,char ** file_type,char ** file_name,const char * json_path)
{
    json j;
    unsigned long num;
    std::ifstream i(json_path);
    i >> j;
    std::cout << j.dump(4) << std::endl;


    num = j.at("modelFileArray").size();
    cout<< "file path num: "<<num<<endl;
    for (unsigned int p=0;p<num;p++)
    {
        json fjson = j.at("modelFileArray")[p];

        //get file path
        string fpath = fjson.at("filePath");
        file_path[p] = new char[128];
        strcpy(file_path[p],fpath.c_str());

        //get file name
        string fname = fjson.at("fileName");
        file_name[p] = new char[128];
        strcpy(file_name[p],fname.c_str());

        //get file type
        json JSmodelType = fjson.at("modelType");
        string ftype = JSmodelType.at("modelTypeValue");
        file_type[p] = new char[128];
        strcpy(file_type[p],ftype.c_str());

        std::cout <<  p<< " path: " <<file_path[p] << std::endl;
        std::cout <<  p<< " type: " <<file_type[p] << std::endl;
        std::cout <<  p<< " name: " <<file_name[p] << std::endl;
    }
    return num;
}


