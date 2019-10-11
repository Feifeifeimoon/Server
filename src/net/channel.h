// Copyright (c) 2019. All rights reserved
#ifndef _SERVER_SRC_NET_CHANNEL_H_
#define _SERVER_SRC_NET_CHANNEL_H_

#include <functional>
#include <utility>

#include "../base/noncopyable.h"


namespace net {
class EventLoop;

class Channel : noncopyable {
 public:
    typedef std::function<void()> EventCallback;
    explicit Channel(int fd, EventLoop* loop);
    ~Channel();

    int fd() const { return socket_fd_; }
    int event() const { return event_; }
    int index() const { return index_; }
    void setIndex(int index) { index_ = index; }

    void update();

    void setReadCallback(EventCallback cb) {readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb);}

    void enableReading()  { event_ |= eReadEvent; update(); }
    void disableReading() { event_ &= ~eReadEvent; update(); }
    void enableWriting()  { event_ |= eWriteEvent; update(); }
    void disableWriting() { event_ &= ~eWriteEvent; update(); }
    void disableAll() { event_ = eNoneEvent; update();}
    bool isNoneEvent() {return event_ == eNoneEvent; }
    void handEvent();
    void remove();
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

    EventCallback readCallback_;
    EventCallback writeCallback_;
};

}  // namespace net


#endif  // _SERVER_SRC_NET_CHANNEL_H_
