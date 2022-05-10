cmake_minimum_required(VERSION 3.21)
project(filessort)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(filessort
        main.cpp
        Loader.cpp
        Matrix.cpp
        Sorter.cpp)
