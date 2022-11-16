//
// Created by sgb on 5/18/22.
//


#include <iostream>

#include "bcflag.h"
#include "cfg.h"
#include "logger.h"
#include "main.h"
#include "json.hpp"
#include "path.h"
#include "magicTime.h"
#include "magicIO.h"

using std::cout;
using std::endl;
using std::string;
using json = nlohmann::json;
using namespace spdlog;

::logger httpLogger("HttpServer",loggerPath,1024*1024*1,1);
HttpServerCfg param;

extern string basePath;

// Handle interrupts, like Ctrl-C
static int s_signo;
static void signal_handler(int signo) {
    s_signo = signo;
}

/*
 * http中断函数
 * */
static void server_fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    if (ev == MG_EV_HTTP_MSG) {
        //hm在整个switch语句里生效，case后加一个{}，限定作用域
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        //在终端打印请求信息
        string method;
        method.assign(hm->method.ptr, hm->method.len);
        string uri;
        uri.assign(hm->uri.ptr, hm->uri.len);

        cout << "method: " << method << endl;
        httpLogger.log->info("method: {}", method);

        cout << "uri: " << uri << endl;
        httpLogger.log->info("uri: {}", uri);

        //匹配本次的请求是否为指定的uri请求
        if (mg_http_match_uri(hm, "/connectTest")) {
            //连接测试
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "------------connectTest-------------" << endl;
            httpLogger.log->info("------------connectTest-------------");
            if (!body.empty()) {
                cout << "------------body:" << body << endl;
                httpLogger.log->debug("------------body: {}", body);
                string stime = settime(body);
                httpLogger.log->info("time_now: {}", stime);
            }
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());
        }


        if (mg_http_match_uri(hm, "/addChipUser")) {
            cout << "------------addChipUser-------------" << endl;
            httpLogger.log->info("------------addChipUser-------------");
            //增加芯片用户，保存用户名密码
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            httpLogger.log->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            httpLogger.log->info("body: {}", body);
            cout << "*****************" << endl;
            ToFile(keyValuePath, body);
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());

        }


        if (mg_http_match_uri(hm, "/endDetect")) {
            cout << "------------endDetect-------------" << endl;
            httpLogger.log->info("------------endDetect-------------");
            //增加芯片用户，保存用户名密码
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            httpLogger.log->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            httpLogger.log->info("body: {}", body);
            cout << "*****************" << endl;
            ToFile(svpStatePath,"0");
            ToFile(fnIdPath,"-1");
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());
        }


        if (mg_http_match_uri(hm, "/modelFile")) {
            cout << "------------modelFile-------------" << endl;
            httpLogger.log->info("------------modelFile-------------");
            //保存文件路径
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            httpLogger.log->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            httpLogger.log->info("body: {}", body);
            cout << "*****************" << endl;
            if (!body.empty()) {
                ToFile(fileAdressPath,body);
                set_flag(HttpServerFlag.c_str(), "1");
                set_flag(svpStatePath.c_str(), "1");
            }
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());

        }


        if (mg_http_match_uri(hm, "/getCurrentFn")) {
            cout << "------------getCurrentFn-------------" << endl;
            httpLogger.log->info("------------getCurrentFn-------------");
            //增加芯片用户，保存用户名密码
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            httpLogger.log->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            httpLogger.log->info("body: {}", body);
            cout << "*****************" << endl;
            if (!ifexists(fnIdPath.c_str())) {
                httpLogger.log->error("not find /app/json/fnId");
                exit(EXIT_FAILURE);
            }
            int fnId = get_flag(fnIdPath.c_str());
            httpLogger.log->info("fnId: {}", fnId);
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "%d",fnId);
        }
    }
}



int main(int argc,char** argv) {
    if (argc != 2)
    {
        cout << "please input cfg path : /**/**/ " << endl;
        exit(1);
    }
    param.init(argv[1],httpLogger.log);
    set_flag(HttpServerFlag.c_str(),"0");
    struct mg_mgr server_mgr;
    mg_mgr_init(&server_mgr);      // Init manager
    mg_http_listen(&server_mgr, param.URL, server_fn, &server_mgr);  // Setup listener
    cout<<"wait listen\r\n" <<endl;
    httpLogger.log->info("wait listen");
    while (s_signo == 0) mg_mgr_poll(&server_mgr, 1000);
    mg_mgr_free(&server_mgr);
    MG_INFO(("Exiting on signal %d", s_signo));
    return 0;
}