//
// Created by Administrator on 2022/6/23.
//
//
// Created by Administrator on 2022/6/23.
//
#include "THFTPAPI.h"
#include <stdio.h>



int main()
{
    char * host = "180.201.4.171";
    int port = 21;
    char* user = "test";
    char* pwd = "123";
    char* data;
    int datalen,filesize;
    int csocket;
    char * source = "/6/test_1660557300477.json";
    char * local = "/home/sgb/tmp/app/model/test1.json";

    csocket = ftp_connect(host, port,user,pwd);
    ftp_list( csocket, ".", &data, &datalen);
    ftp_retrfile( csocket,source, local ,&filesize,NULL);

    printf("data:%s\r\n",data);
    printf("ret : %d",csocket);
    return 0;


}
