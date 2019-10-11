// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_EVENTLOOPTHREAD_H_
#define _SERVER_SRC_NET_EVENTLOOPTHREAD_H_

#include <thread> // NOLINT
#include <mutex> // NOLINT
#include <condition_variable> // NOLINT

#include "../base/noncopyable.h"



namespace net {

class EventLoop;

class EventLoopThread : public noncopyable {
 public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startLoop();

 private:
    void threadFunc();

    std::thread thread_;
    EventLoop* eventLoop_;
    std::mutex mutex_;
    std::condition_variable cond_;
};


}  // namespace net


#endif  // _SERVER_SRC_NET_EVENTLOOPTHREAD_H_
