//
// Created by Administrator on 2022/11/11.
//

#ifndef HTTPSERVER_MAGICIO_H
#define HTTPSERVER_MAGICIO_H
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>  // exit()
#include <sys/stat.h>  // stat()

using std::string;

int getFileSize(const string &filePath)
{
    struct stat statbuf;
    stat(filePath.c_str(),&statbuf);
    int size=statbuf.st_size;

    return size;
}

void ToFile(const string &filepath, const string &data)
{
    FILE *tfp = NULL;
    tfp = fopen(filepath.c_str(), "w");
    if(tfp == NULL){
        std::cout << "open file: " << filepath << " error" << std::endl;
        exit(EXIT_FAILURE);
    }
    fputs(data.c_str(), tfp);
    fclose(tfp);
}

/*
 * get_flag：获取标志文件某一标志位值
 * 输入：file_path 文件路径
 *      flag_name 标志名称
 * 返回值：标志位值
 * */
void ReadFile(const string &filePath, string &data)
{
    //判断是否有目标
    int svp_flag=0;
    FILE *fp = NULL;
    int filesize = getFileSize(filePath);
    char* buff = new char [filesize];
    fp = fopen(filePath.c_str(), "r");
    if(fp == NULL){
        std::cout << "open file: " << filePath << " error" << std::endl;
        exit(EXIT_FAILURE);
    }
    fgets(buff, filesize+1, (FILE*)fp);
    data = buff;
    fclose(fp);
    delete[] buff;
}


#endif //HTTPSERVER_MAGICIO_H
