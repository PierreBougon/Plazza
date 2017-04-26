cmake_minimum_required(VERSION 3.6)
project(cpp_plazza)

set(CMAKE_CXX_STANDARD 14)

include_directories(include
        /home/sauvau_m/Qt5.8.0/5.8/gcc_64/include
        )

file(GLOB_RECURSE SOURCE_FILES
        "include/*.hpp"
        "src/*.cpp")

add_executable(cpp_plazza ${SOURCE_FILES})
