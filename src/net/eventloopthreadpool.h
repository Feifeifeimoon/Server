// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_EVENTLOOPTHREADPOOL_H_
#define _SERVER_SRC_NET_EVENTLOOPTHREADPOOL_H_


#include <vector>
#include <memory>
#include "../base/noncopyable.h"

namespace net {
class EventLoopThread;
class EventLoop;

class EventLoopThreadPool : public noncopyable {
 public:
    EventLoopThreadPool(EventLoop* loop, int num);
    ~EventLoopThreadPool();
    EventLoop* getNextLoop();
    void start();
    void stop();
 private:
    int threadNum_;
    int nextIndex_;
    EventLoop* baseLoop_;
    std::vector<EventLoop*> loops_;
    std::vector<std::unique_ptr<EventLoopThread> > threads_;
};

}  // namespace net

#endif  // _SERVER_SRC_NET_EVENTLOOPTHREADPOOL_H_
