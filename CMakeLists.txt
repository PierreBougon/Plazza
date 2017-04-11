cmake_minimum_required(VERSION 3.6)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES
        "include/*.hpp"
        "src/*.cpp")
add_executable(cpp_plazza ${SOURCE_FILES})