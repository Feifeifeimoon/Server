// Copyright (c) 2019. All rights reserved


#ifndef _SERVER_SRC_NET_CONNECTOR_H_
#define _SERVER_SRC_NET_CONNECTOR_H_


#include <functional>
#include <memory>

#include "../base/noncopyable.h"
#include "socket.h" // NOLINT

namespace net {

class EventLoop;
class Socket;
class Channel;


// 继承 enable_shared_from_this 为了能够使用shared_from_this
class Connector : noncopyable,
                  public std::enable_shared_from_this<Connector>{
    typedef std::function<void(const std::shared_ptr<Connector>&)> CloseCallback;
 public:
    Connector(int fd, EventLoop* loop);
    ~Connector();

    void send(const char* buffer, size_t len);
    void close();
    int fd() const { return  socket_->fd(); }

    void setCloseCallback(const CloseCallback& cb) { closeCallback_ = cb;}
 private:
    void handleRead();
    void handleWrite();
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    EventLoop* loop_;
    CloseCallback closeCallback_;
};

}  // namespace net

#endif  // _SERVER_SRC_NET_CONNECTOR_H_
