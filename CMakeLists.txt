cmake_minimum_required(VERSION 3.31)
project(neural C)

set(CMAKE_C_STANDARD 11)

add_executable(neural main.c
        init.h
        printer.h
        update.h
        imports.h)
