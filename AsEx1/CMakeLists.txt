cmake_minimum_required(VERSION 3.6)
project(AsEx1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES

    finddupl.c
        mentry.c
    mentry.h

    mlist.h
    mlistLL.c)

add_executable(AsEx1 ${SOURCE_FILES})