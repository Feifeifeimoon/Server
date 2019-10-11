// Copyright (c) 2019. All rights reserved
#include "connector.h"  // NOLINT

#include <glog/logging.h>
#include <string>
#include <memory>
#include "socket.h" // NOLINT
#include "channel.h" // NOLINT
#include "eventloop.h" // NOLINT

using net::Connector;
using net::Socket;
using net::Channel;
using net::EventLoop;

#define BUFFSIZE 1024

Connector::Connector(int fd, net::EventLoop *loop)
    : socket_(new Socket(fd)),
      channel_(new Channel(fd, loop)),
      loop_(loop) {
    channel_->setReadCallback(std::bind(&Connector::handleRead, this));
    channel_->setWriteCallback(std::bind(&Connector::handleWrite, this));
    channel_->enableReading();
}

void Connector::send(const char *buffer, size_t len) {
    socket_->send(buffer, len);
}

void Connector::close() {
    channel_->disableAll();
}

void Connector::handleRead() {
    std::string buf;
    char tmpBuf[BUFFSIZE] = {};
    //因为是边缘触发模式，每一次都要读完所有数据
    size_t count = 0, countAll = 0;

    do {
        count = socket_->recv(tmpBuf, sizeof(tmpBuf));
        countAll += count;
        buf.append(tmpBuf, 0, count);
    } while (count == BUFFSIZE);

    if (count < 0) {
        LOG(ERROR) << "recv failed" << strerror(errno);
        return;
    } else if (count == 0) {
        channel_->disableAll();
        if (closeCallback_)
            closeCallback_(shared_from_this());
        return;
    }

    LOG(INFO) << "recv " << countAll << " message: " << buf;
}


void Connector::handleWrite() {}

Connector::~Connector() {
    LOG(INFO) << "~Connector";
    channel_->remove();
}
