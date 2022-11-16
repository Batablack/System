//
// Created by Administrator on 2022/11/11.
//

#ifndef HTTPSERVER_MAGICTIME_H
#define HTTPSERVER_MAGICTIME_H
#include <string>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <stdlib.h> //system()

using std::cout;
using std::endl;

std::string settime(const std::string stime)
{
    int itime = atoi(stime.c_str()) + 8*3600;
    time_t ntime =(time_t)itime;
    struct tm * ctime = gmtime(&ntime);
    cout << "time_now:" << asctime(ctime) << endl;
    char datetime[256] = {};
    sprintf(datetime,"date -s \"%d-%d-%d %02d:%02d:%02d\"",ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour,ctime->tm_min,ctime->tm_sec);
    system(datetime);
    system("hwclock -w");
    std::string tmpTime = asctime(ctime);
    return tmpTime;
}

#endif //HTTPSERVER_MAGICTIME_H
