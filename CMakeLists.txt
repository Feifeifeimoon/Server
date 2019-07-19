cmake_minimum_required(VERSION 2.8)
project(Server)

set(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY( src/net )
ADD_SUBDIRECTORY( src/base )

add_executable(Server main.cpp)
TARGET_LINK_LIBRARIES(Server net base)