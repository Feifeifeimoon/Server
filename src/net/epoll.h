// Copyright (c) 2019. All rights reserved


#ifndef  _SERVER_SRC_NET_EPOLL_H_
#define  _SERVER_SRC_NET_EPOLL_H_

#include <sys/epoll.h>
#include <vector>
#include <map>

#include "../base/noncopyable.h"

struct epoll_event;

namespace net {

class Channel;

class EPoll : noncopyable {
 public:
    EPoll();
    ~EPoll();

    void poll();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

    void update(int operation, Channel* channel);
 private:
    const int epoll_fd_;
    std::vector<struct epoll_event> events_;
    std::map<int, Channel*> channels_;
};

}  // namespace net

#endif  // _SERVER_SRC_NET_EPOLL_H_
