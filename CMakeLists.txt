cmake_minimum_required(VERSION 3.26)
project(EasyX_test1)

set(CMAKE_CXX_STANDARD 17)

link_libraries(libeasyx.a)

#include_directories("C:/Users/CHH/Pictures/Wallhaven")

add_executable(EasyX_test1 main.cpp
        Widget.cpp
        Widget.h
        Point.cpp
        Point.h
        Ellipse.cpp
        Ellipse.h
        twoballsmove.cpp
        twoballsmove.h
        Showellipse.cpp
        Showellipse.h)
