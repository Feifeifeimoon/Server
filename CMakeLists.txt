cmake_minimum_required(VERSION 2.8)
project(Server)
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY( src/net )
ADD_SUBDIRECTORY( src/base )

add_executable(Server main.cpp)
TARGET_LINK_LIBRARIES(Server net base glog pthread)