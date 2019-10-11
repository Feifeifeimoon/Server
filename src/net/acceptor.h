// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_ACCEPTOR_H_
#define _SERVER_SRC_NET_ACCEPTOR_H_

#include <map>
#include <memory>
#include <utility>
#include <functional>

#include "../base/noncopyable.h"

namespace net {

class Socket;
class Channel;
class EventLoop;
class Connector;

class Acceptor : noncopyable {
    typedef std::function<void(int)> AcceptCallback;
 public:
    Acceptor(EventLoop* loop, const char* ip, int port);
    ~Acceptor();
    void handleRead();
    void setAcceptCallback(AcceptCallback cb) {acceptCallback_ = std::move(cb);}
 private:
    EventLoop* loop_;
    // Socket* acceptSocket_;
    std::unique_ptr<Socket> acceptSocket_;
    std::unique_ptr<Channel> acceptChannel_;
    // Channel* acceptChannel_;
    AcceptCallback acceptCallback_;
};

}  // namespace net



#endif  // _SERVER_SRC_NET_ACCEPTOR_H_
