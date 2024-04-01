cmake_minimum_required(VERSION 3.27)
project(HW2)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW2 netOmsterdam.cpp
        Graph.cpp
        Graph.h
        Station.cpp
        Station.h
        Transport.cpp
        Transport.h
        Bus.h
        Tram.h
        Sprinter.h
        Rail.h
        Bus.cpp
        Sprinter.cpp
        Tram.cpp
        Rail.cpp
        Intercity.cpp
        Intercity.h
        Stad.cpp
        Stad.h
        Central.cpp
        Central.h)
