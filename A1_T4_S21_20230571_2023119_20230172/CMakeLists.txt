cmake_minimum_required(VERSION 3.27)
project(A1_T4_S21_20230571_2023119_20230172)

set(CMAKE_CXX_STANDARD 17)

add_executable(A1_T4_S21_20230571_2023119_20230172 main.cpp
        Instructions.h
        Instructions.cpp
        Register.h
        Register.cpp
        Memory.h
        Memory.cpp
        ALU.h
        ALU.cpp
        CPU.h
        CPU.cpp)
