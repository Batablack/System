//
// Created by Administrator on 2022/11/11.
//
#include "magicIO.h"
#include "../src/json.hpp"
#include "../src/path.h"
#include <string>
#include <iostream>
using nlohmann::json;
using std::string;
int main(int argc,char** argv)
{
    if (argc != 2){
        exit(1);
    }
    json j;
    j["testnum"] = 3;
    j["teststring"] = "abcde";
    string data = j.dump();
    ToFile("/home/sgb/mnt/test/testfile",data);
    std::cout << "write test file done "<< std::endl;
    string rdata;
    ReadFile("/home/sgb/mnt/test/testfile",rdata);
    std::cout << "read test file done "<< std::endl;
    std::cout << "test read invalid file"<< std::endl;
    ReadFile("/home/sgb/mnt/test/testfile01",rdata);
    std::cout << "data :" << rdata << std::endl;
}
