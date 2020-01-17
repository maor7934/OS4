cmake_minimum_required(VERSION 3.15)
project(OS4)

set(CMAKE_CXX_STANDARD 11)

add_executable(OS4 Barrier.h ThreadSafeList.h Barrier.cpp listTest.cpp)