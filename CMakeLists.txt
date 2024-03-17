cmake_minimum_required(VERSION 3.27)
project(HW2)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW2 main.cpp
        Graph.cpp
        Graph.h
        Station.cpp
        Station.h
        Transport.cpp
        Transport.h)
