// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_SOCKET_H_
#define _SERVER_SRC_NET_SOCKET_H_

#include <cstdint>
#include <cstddef>
#include "../base/noncopyable.h"

namespace net {

class Socket : noncopyable{
 public:
    explicit Socket(int socket_fd) : socket_fd_(socket_fd) { }

    ~Socket();

    int fd() const { return socket_fd_; }

    void bind(const char* ip, const uint16_t port);

    void listen();

    int accept();

    size_t recv(char* buffer, size_t count);

    size_t send(const char* buffer, size_t len);

    void setReuseAddr(bool on);
 private:
    int socket_fd_;
};


}  // namespace net

#endif  // _SERVER_SRC_NET_SOCKET_H_
