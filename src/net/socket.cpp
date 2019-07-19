// Copyright (c) 2019. All rights reserved
#include <unistd.h>
#include <sys/socket.h>
#include "socket.h"



void Socket::listen() {
    ::listen(socket_fd_, 50);
    return void();
}

Socket::~Socket() {
    ::close(socket_fd_);
}
