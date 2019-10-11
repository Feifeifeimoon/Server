// Copyright (c) 2019. All rights reserved

#include "eventloop.h" // NOLINT
#include <glog/logging.h>
#include "./epoll.h"

using net::EventLoop;
using net::EPoll;


EventLoop::EventLoop() : quit_(false), poller_(new EPoll()) {}

void EventLoop::loop() {
    while (!quit_) {
        poller_->poll();
        // LOG(INFO) << "once loop";
    }
    LOG(INFO) << "event loop quit";
}

void EventLoop::quit() {
    quit_ = true;
}


void EventLoop::updateChannel(net::Channel *channel) {
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(net::Channel *channel) {
    poller_->removeChannel(channel);
}

EventLoop::~EventLoop() {
    LOG(INFO) << "~EventLoop";
    delete poller_;
}

