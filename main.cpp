
#include <sys/socket.h>

#include <glog/logging.h>
#include "src/net/socket.h"

int main() {
//    google::InitGoogleLogging("");
//    google::SetLogDestination(google::GLOG_INFO, "/tmp/log/log_info_");
//    google::SetLogDestination(google::GLOG_ERROR, "/tmp/log/log_error_");
//    google::SetLogDestination(google::GLOG_FATAL, "/tmp/log/log_fatal_");
    LOG(INFO) << "-- start --";
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    net::Socket test(fd);
    test.setReuseAddr(true);
    test.bind("127.0.0.1", 9000);
    test.listen();
    char buffer[1024] = {};
    for (;;){
        int cli_fd = test.accept();
        read(cli_fd, buffer, sizeof(buffer));
        LOG(INFO) << buffer;
    }
    return 0;
}

