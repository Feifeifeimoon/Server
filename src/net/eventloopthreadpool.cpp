// Copyright (c) 2019. All rights reserved

#include "eventloopthreadpool.h" // NOLINT

#include <glog/logging.h>
#include "eventloop.h" // NOLINT
#include "eventloopthread.h" // NOLINT

using net::EventLoopThreadPool;
using net::EventLoopThread;
using net::EventLoop;

EventLoopThreadPool::EventLoopThreadPool(EventLoop* loop, int num)
    : threadNum_(num),
      nextIndex_(0),
      baseLoop_(loop) {
}



EventLoop* EventLoopThreadPool::getNextLoop() {
    // assert(!loops_.empty());
    EventLoop* loop = baseLoop_;
    if (!loops_.empty()) {
        loop = loops_[nextIndex_];
        nextIndex_ = nextIndex_ + 1 == static_cast<int >(loops_.size()) ?
                0 : nextIndex_ + 1;
    }
    return loop;
}


void EventLoopThreadPool::start() {
    // baseLoop_->poll();

    for (int i = 0; i < threadNum_; ++i) {
        EventLoopThread* eventLoopThread = new EventLoopThread();
        auto eventLoop = eventLoopThread->startLoop();
        threads_.push_back(std::unique_ptr<EventLoopThread>(eventLoopThread));
        loops_.push_back(eventLoop);
    }
    LOG(INFO) << "ThreadPool Running :" << threadNum_;
    baseLoop_->loop();
}

void EventLoopThreadPool::stop() {
    baseLoop_->quit();
    for (auto item : loops_) {
        item->quit();
    }
}

net::EventLoopThreadPool::~EventLoopThreadPool() {
    LOG(INFO) << "~EventLoopThreadPool";
}
