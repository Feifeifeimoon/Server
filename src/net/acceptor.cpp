// Copyright (c) 2019. All rights reserved

#include "./acceptor.h" // NOLINT

#include <sys/socket.h>
#include <netinet/in.h>

#include <glog/logging.h>
#include "./socket.h"  // NOLINT
#include "./channel.h"
#include "./connector.h"

using net::Acceptor;
using net::Socket;
using net::Channel;
using net::Connector;

Acceptor::Acceptor(EventLoop* loop, const char *ip, int port)
    : loop_(loop),
      acceptSocket_(new Socket(socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0))), // NOLINT
      acceptChannel_(new Channel(acceptSocket_->fd(), loop)) {

    acceptSocket_->setReuseAddr(true);
    acceptSocket_->bind(ip, port);
    acceptSocket_->listen();
    acceptChannel_->setReadCallback(std::bind(&Acceptor::handleRead, this));
    acceptChannel_->enableReading();
}

/*
 * 有新客户端连接时
 */
void Acceptor::handleRead() {
    int cli_fd = acceptSocket_->accept();
    if (cli_fd < 0) {
        LOG(ERROR) << "accept error";
    } else {
        acceptCallback_(cli_fd);
    }
//    Connector* conn = new Connector(cli_fd, loop_);
//    conns_[cli_fd] = conn;
//    LOG(INFO) << "now have conns: " << conns_.size();
}

Acceptor::~Acceptor() {
    LOG(INFO) << "~Acceptor";
}



