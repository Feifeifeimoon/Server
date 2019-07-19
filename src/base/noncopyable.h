// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_BASE_NONCOPYABLE_H_
#define _SERVER_SRC_BASE_NONCOPYABLE_H_

class noncopyable {
 public:
    noncopyable(const noncopyable&) = delete;
    void operator = (const noncopyable&) = delete;

 protected:
    noncopyable() = default;
    ~noncopyable() = default;
};

#endif  // _SERVER_SRC_BASE_NONCOPYABLE_H_
