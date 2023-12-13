cmake_minimum_required (VERSION 3.8)
set(PROJECT
    mymod
)
project ({PROJECT} VERSION 0.0.1 LANGUAGES CXX)

message(STATUS "System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})
message(STATUS "CMake generates " ${CMAKE_GENERATOR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
#FetchContent_Declare(pybind11 URL https://github.com/pybind/pybind11/archive/refs/tags/v2.11.1.tar.gz)
FetchContent_Declare(pybind11 URL https://github.com/pybind/pybind11/archive/refs/heads/smart_holder.zip)
FetchContent_MakeAvailable(pybind11)

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

pybind11_add_module(${PROJECT} ${SOURCES})
install(TARGETS ${PROJECT} DESTINATION ${CMAKE_INSTALL_BINDIR})