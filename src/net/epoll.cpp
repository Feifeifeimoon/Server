// Copyright (c) 2019. All rights reserved

#include "epoll.h"  // NOLINT

#include <sys/epoll.h>

#include <glog/logging.h>
#include "./channel.h"

using net::EPoll;

static const int MAX_EVENTS = 20;


EPoll::EPoll()
    : epoll_fd_(::epoll_create1(EPOLL_CLOEXEC)),
      events_(MAX_EVENTS) {
    if (epoll_fd_ < 0) {
        LOG(FATAL) << "epoll_create1 failed" << strerror(errno);
    }
}

void EPoll::poll() {
    int event_num = ::epoll_wait(epoll_fd_, &*events_.begin(),
                                 events_.size(), -1);
    if (event_num < 0) {
        LOG(ERROR) << "epoll_wait filed" << strerror(errno);
    } else if (event_num == 0) {
        LOG(INFO) << "no event happened";
    }
}


void EPoll::updateChannel(net::Channel *channel) {
    int index = channel->index();
    int fd = channel->fd();
    if (index == -1) {
        channels_[fd] = channel;
    }
}


void EPoll::update(int operation, net::Channel *channel) {
    struct epoll_event event = { };
    event.data.ptr = reinterpret_cast<void*>(&channel);
}

EPoll::~EPoll() {
    ::close(epoll_fd_);
}
