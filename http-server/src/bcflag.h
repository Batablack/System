//
// Created by Administrator on 2022/8/16.
//

#ifndef DOWNLOADWK_DEMO_BCFLAG_H
#define DOWNLOADWK_DEMO_BCFLAG_H
#include <sys/stat.h>
#include <string>

/*
 * ifexists:判断某一文件是否存在
 * return：存在1，不存在0
 * */
inline bool ifexists (const char* name) {
    struct stat buffer;
    return (stat (name, &buffer) == 0);
}

int set_flag(const char* file_path,const char* flag);
int get_flag(const char* file_path);

#endif //DOWNLOADWK_DEMO_BCFLAG_H
