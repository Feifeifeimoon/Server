
#include <csignal>
#include <thread>
#include <sys/syscall.h>
#define gettid() syscall(__NR_gettid)
#include <glog/logging.h>
#include "src/net/tcpserver.h"

net::TcpServer* tcpServer = nullptr;

void signalDeal(int sig) {
    LOG(INFO) << "收到退出信号" << sig;
    delete tcpServer;
    google::ShutdownGoogleLogging();
    exit(0);
}

int main(int argc, char* argv[]) {
//    google::InitGoogleLogging(argv[0]);
//    google::SetLogDestination(google::GLOG_INFO, "/server/log/log_info_");
//    google::SetLogDestination(google::GLOG_ERROR, "/server/log/log_error_");
//    google::SetLogDestination(google::GLOG_FATAL, "/server/log/log_fatal_");
//    //缓存的最大时长，超时会写入文件
//    FLAGS_logbufsecs = 1;
    //signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, signalDeal);
    LOG(INFO) << "------ start -------" << gettid();
    tcpServer = new net::TcpServer("127.0.0.1",9000);
    tcpServer->run();
    return 0;
}

