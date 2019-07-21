// Copyright (c) 2019. All rights reserved
#ifndef _SERVER_SRC_NET_CHANNEL_H_
#define _SERVER_SRC_NET_CHANNEL_H_

#include "../base/noncopyable.h"

namespace net {
class EventLoop;

class Channel : noncopyable {
 public:
    explicit Channel(int fd, EventLoop* loop);
    ~Channel();

    int fd() const { return socket_fd_; }
    int event() const { return event_; }
    int index() const { return index_; }
    void setIndex(int index) { index_ = index; }

    void update();

    void enableReading()  { event_ |= eReadEvent; update(); }
    void disableReading() { event_ &= ~eReadEvent; update(); }
    void enableWriting()  { event_ |= eWriteEvent; update(); }
    void disableWriting() { event_ &= ~eWriteEvent; update(); }

 private:
    // 事件
    static const int eNoneEvent;
    static const int eReadEvent;
    static const int eWriteEvent;
    // socket描述符
    int socket_fd_;
    // 当前的监听的时间
    int event_;
    // Channel所属的loop
    EventLoop* loop_;
    int index_;
};

}  // namespace net


#endif  // _SERVER_SRC_NET_CHANNEL_H_
