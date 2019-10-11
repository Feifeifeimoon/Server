// Copyright (c) 2019. All rights reserved

#include "eventloopthread.h" // NOLINT
#include <glog/logging.h>
#include <functional>
#include "eventloop.h" // NOLINT

net::EventLoopThread::EventLoopThread() : eventLoop_(nullptr) {}

net::EventLoop *net::EventLoopThread::startLoop() {
    thread_ = std::thread(std::bind(&EventLoopThread::threadFunc, this));

    {
        std::unique_lock <std::mutex> lck(mutex_);
        while (eventLoop_ == nullptr) {
            cond_.wait(lck);
        }
    }
    return eventLoop_;
}


void net::EventLoopThread::threadFunc() {
    // 在栈上申请，这样结束后自动释放内存
    EventLoop loop;
    {
        std::lock_guard<std::mutex> lck(mutex_);
        eventLoop_ = &loop;
        cond_.notify_all();
    }
    loop.loop();
    eventLoop_ = nullptr;
}

net::EventLoopThread::~EventLoopThread() {
    LOG(INFO) << "~EventLoopThread";
    thread_.join();
}

