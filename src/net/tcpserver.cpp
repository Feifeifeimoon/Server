// Copyright (c) 2019. All rights reserved

#include "tcpserver.h"  // NOLINT
#include <glog/logging.h>
#include <memory>
#include "eventloop.h"  // NOLINT
#include "acceptor.h"  // NOLINT
#include "connector.h"  // NOLINT
#include "eventloopthreadpool.h"  // NOLINT

using net::TcpServer;
using net::Acceptor;
using net::EventLoop;
using net::Connector;


TcpServer::TcpServer(const char *ip, int port)
    : count_(0),
      loop_(new EventLoop),
      threadPool_(new EventLoopThreadPool(loop_, 2)),
      acceptor_(new Acceptor(loop_, ip, port)) {
    acceptor_->setAcceptCallback(
            std::bind(&TcpServer::newConn, this, std::placeholders::_1));
}


void TcpServer::run() {
    threadPool_->start();
}


void TcpServer::newConn(int fd) {
    auto loop = threadPool_->getNextLoop();
    // Connector* conn = new Connector(fd, loop);
    std::shared_ptr<Connector> conn(new Connector(fd, loop));
    conn->setCloseCallback(
            std::bind(&TcpServer::onClose, this, std::placeholders::_1));
    conns_[fd] = conn;
    count_++;
    LOG(INFO) << "new conn join, now have conns: " << count_;
}

void TcpServer::onClose(const std::shared_ptr<Connector> &conn) {
    LOG(INFO) << "dtor 1";
    conns_.erase(conn->fd());
    LOG(INFO) << "dtor 2";
    count_--;
    LOG(INFO) << "one conn exit, now have conns: " << count_;
}

TcpServer::~TcpServer() {
    LOG(INFO) << "~TcpServer";
    threadPool_->stop();
    for (auto& item : conns_) {
        item.second->close();
    }
    delete(loop_);
}
