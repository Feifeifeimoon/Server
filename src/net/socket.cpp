// Copyright (c) 2019. All rights reserved
#include "socket.h" // NOLINT

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <glog/logging.h>

using net::Socket;


void Socket::bind(const char *ip, const uint16_t port) {
    struct sockaddr_in socket_addr = {};
    bzero(&socket_addr, sizeof(socket_addr));
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(port);
    inet_aton(ip, &socket_addr.sin_addr);
    int ret = ::bind(socket_fd_, reinterpret_cast<sockaddr*>(&socket_addr),
                     static_cast<socklen_t>(sizeof(socket_addr)));
    if (ret < 0) {
        LOG(FATAL) << "bind failed: " << strerror(errno);
    }
}


void Socket::listen() {
    int ret = ::listen(socket_fd_, SOMAXCONN);
    if (ret < 0) {
        LOG(FATAL) << "listen failed: " << strerror(errno);
    }
}

int Socket::accept() {
    struct sockaddr_in cli_addr = {};
    socklen_t addr_len = 0;
    bzero(&cli_addr, sizeof(cli_addr));
    // accept4直接返回非阻塞的socket
    int conn_fd = ::accept4(socket_fd_, reinterpret_cast<sockaddr*>(&cli_addr),
                           &addr_len, SOCK_NONBLOCK);
    if (conn_fd < 0) {
        LOG(ERROR) << "accept failed" << strerror(errno);
        return -1;
    }
    LOG(INFO) << "recv conn from :" << inet_ntoa(cli_addr.sin_addr) \
              << cli_addr.sin_port;
    return conn_fd;
}

size_t Socket::recv(char *buffer, size_t count) {
    return ::recv(socket_fd_, buffer, count, 0);
}


size_t Socket::send(const char *buffer, size_t len) {
    return ::send(socket_fd_, buffer, len, 0);
}


void Socket::setReuseAddr(bool on) {
    int option_value = on?  1 : 0;
    ::setsockopt(socket_fd_, SOL_SOCKET, SO_REUSEADDR, &option_value,
                 static_cast<socklen_t >(sizeof(option_value)));
}

Socket::~Socket() {
    LOG(INFO) << "~Socket";
    ::close(socket_fd_);
}
