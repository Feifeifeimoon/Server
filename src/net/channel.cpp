// Copyright (c) 2019. All rights reserved
#include "channel.h"  // NOLINT

#include <sys/epoll.h>
#include <glog/logging.h>
#include "./eventloop.h"
using net::Channel;

const int Channel::eNoneEvent = 0;
// EPOLLIN：对应的文件描述有可以读取的内容
// EPOLLPRI：发生异常情况
// EPOLLET:指定使用边缘触发模式
const int Channel::eReadEvent = EPOLLIN | EPOLLPRI | EPOLLET;
// EPOLLOUT：对应的文件描述符有可以写入
const int Channel::eWriteEvent = EPOLLOUT;


Channel::Channel(int fd, EventLoop* loop)
    : socket_fd_(fd),
      event_(eNoneEvent),
      loop_(loop),
      index_(-1) {
}


void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::handEvent() {
    if (event_ & EPOLLIN) {
        if (readCallback_) readCallback_();
    } else if (event_ & EPOLLOUT) {
        if (writeCallback_) writeCallback_();
    }
}

void Channel::remove() {
    loop_->removeChannel(this);
}

Channel::~Channel() {
    LOG(INFO) << "~Channel";
}
