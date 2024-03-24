cmake_minimum_required(VERSION 3.27)
project(HW2)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW2 main.cpp
        Graph.cpp
        Graph.h
        Station/Station.cpp
        Station/Station.h
        Transport/Transport.cpp
        Transport/Transport.h
        Transport/Bus.h
        Transport/Tram.h
        Transport/Sprinter.h
        Transport/Rail.h
        Transport/Bus.cpp
        Transport/Sprinter.cpp
        Transport/Tram.cpp
        Transport/Rail.cpp
        Station/Intercity.cpp
        Station/Intercity.h
        Station/Stad.cpp
        Station/Stad.h
        Station/Central.cpp
        Station/Central.h)
