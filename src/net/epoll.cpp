// Copyright (c) 2019. All rights reserved

#include "epoll.h"  // NOLINT

#include <sys/epoll.h>

#include <glog/logging.h>
#include "./channel.h"

using net::EPoll;
using net::Channel;

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
                                 events_.size(), 1000);
    if (event_num < 0) {
        LOG(ERROR) << "epoll_wait filed" << strerror(errno);
        return;
    } else if (event_num == 0) {
        // LOG(INFO) << "no event happened";
        return;
    }
    LOG(INFO) << event_num << " evens happened";
    for (int i = 0; i < event_num; ++i) {
        auto channel = static_cast<Channel*>(events_[i].data.ptr);
        // LOG(INFO) << "fd:" << channel->fd() << "  happened";
        channel->handEvent();
    }
}


void EPoll::updateChannel(Channel* channel) {
    int index = channel->index();
    int fd = channel->fd();
    if (index == -1) {
        channels_[fd] = channel;
        channel->setIndex(fd);
        update(EPOLL_CTL_ADD, channel);
    } else {
        if (channel->isNoneEvent()) {
            update(EPOLL_CTL_DEL, channel);
        } else {
            update(EPOLL_CTL_MOD, channel);
        }
    }
    LOG(INFO) << "  have conns:" << channels_.size();
}

void EPoll::removeChannel(net::Channel *channel) {
    int index = channel->index();
    int fd = channel->fd();
    if (index == -1) {
        return ;
    }
    channels_.erase(fd);
}

void EPoll::update(int operation, Channel* channel) {
    struct epoll_event event = { };
    event.data.ptr = static_cast<void*>(channel);
    event.events = channel->event();
    int fd = channel->fd();
    if (::epoll_ctl(epoll_fd_, operation, fd, &event) < 0) {
        LOG(ERROR) << "epoll ctl failed" << strerror(errno);
    }
}

EPoll::~EPoll() {
    ::close(epoll_fd_);
}
