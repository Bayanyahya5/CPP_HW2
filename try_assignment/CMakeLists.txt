cmake_minimum_required(VERSION 3.28)
project(CPP_HW2_CLION)

set(CMAKE_CXX_STANDARD 20)

add_executable(CPP_HW2_CLION main.cpp
        battery_meter.h
        MyAlgorithm.cpp
        MyBattery_meter.cpp
        MyDirt_sensor.cpp
        MySimulator.cpp
        MyWall_sensor.cpp)
