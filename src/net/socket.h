// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_SOCKET_H_
#define _SERVER_SRC_NET_SOCKET_H_

#include "../base/noncopyable.h"

class Socket : noncopyable{
 public:
    explicit Socket(int socket_fd) : socket_fd_(socket_fd) { }
    ~Socket();
    int fd() const { return socket_fd_; }
    void listen();
 private:
    int socket_fd_;
};


#endif  // _SERVER_SRC_NET_SOCKET_H_
