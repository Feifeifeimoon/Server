// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_EVENTLOOP_H_
#define _SERVER_SRC_NET_EVENTLOOP_H_

#include "../base/noncopyable.h"

namespace net {

class EPoll;
class Channel;

class EventLoop : noncopyable {
 public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

 private:
    bool quit_;
    EPoll* poller_;
};

}  // namespace net

#endif  // _SERVER_SRC_NET_EVENTLOOP_H_
