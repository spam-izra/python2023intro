cmake_minimum_required (VERSION 3.8)
set(PROJECT mymod)
project(${PROJECT})

message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMake generates " ${CMAKE_GENERATOR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADERS
    "include/*.h"
    "include/*.hpp"
    "include/*.inl"
)

file(GLOB_RECURSE SOURCES
    "src/*.c"
    "src/*.cpp"
    "src/*.cxx"
)

include_directories(
     "include"
)

message(STATUS "SRC: " ${SOURCES})

add_library(${PROJECT} SHARED ${SOURCES})
install(TARGETS ${PROJECT}
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX})