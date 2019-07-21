// Copyright (c) 2019. All rights reserved

#ifndef _SERVER_SRC_NET_ACCEPTOR_H_
#define _SERVER_SRC_NET_ACCEPTOR_H_

#include <cstdint>

#include "../base/noncopyable.h"

namespace net {

class Socket;

class Acceptor : noncopyable {
 public:
    Acceptor(const char* ip, const uint16_t port);

 private:
    Socket* acceptSocket;
};

}  // namespace net



#endif  // _SERVER_SRC_NET_ACCEPTOR_H_
