// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_EVENTLOOP_H_
#define _SERVER_SRC_NET_EVENTLOOP_H_

#include "../base/noncopyable.h"

namespace net {

class EventLoop : noncopyable {
 public:
    EventLoop();
};

}  // namespace net

#endif  // _SERVER_SRC_NET_EVENTLOOP_H_
