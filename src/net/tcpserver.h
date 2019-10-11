// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_TCPSERVER_H_
#define _SERVER_SRC_NET_TCPSERVER_H_


#include <map>
#include <memory>
#include <atomic>
#include "../base/noncopyable.h"

namespace net {

class Acceptor;
class Connector;
class EventLoop;
class EventLoopThreadPool;

class TcpServer : noncopyable{
 public:
    TcpServer(const char* ip, int port);
    ~TcpServer();
    void run();

    void newConn(int fd);
    void onClose(const std::shared_ptr<Connector>& conn);
 private:
    std::atomic_int count_;
    EventLoop* loop_;
    // EventLoopThreadPool* threadPool_;
    std::unique_ptr<EventLoopThreadPool> threadPool_;
    std::unique_ptr<Acceptor> acceptor_;
    // Acceptor* acceptor_;
    std::map<int, std::shared_ptr<Connector>> conns_;
};


}  // namespace net

#endif  // _SERVER_SRC_NET_TCPSERVER_H_
