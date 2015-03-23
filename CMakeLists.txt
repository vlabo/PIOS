cmake_minimum_required(VERSION 3.1)
project(PIOS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    source/assembly.h
    source/basic.h
    source/boot.asm
    source/gpio.asm
    source/main.cpp
    source/systemTimer.asm
    kernel.list
    Makefile)

add_executable(PIOS ${SOURCE_FILES})