cmake_minimum_required(VERSION 3.6)
project(JobShop)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES jobshop/main.cpp jobshop/solution.cpp jobshop/input_output.cpp)
file(GLOB SOURCES
        *.h
        *.cpp
        )

add_executable(JobShop ${SOURCE_FILES} ${SOURCES})
