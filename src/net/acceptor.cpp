// Copyright (c) 2019. All rights reserved

#include "./acceptor.h" // NOLINT

#include <sys/socket.h>

#include "./socket.h"  // NOLINT

using net::Acceptor;
using net::Socket;

Acceptor::Acceptor(const char *ip, const uint16_t port) {
    acceptSocket = new Socket(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0));
    acceptSocket->setReuseAddr(true);
    acceptSocket->bind(ip, port);
    acceptSocket->listen();
}

