cmake_minimum_required(VERSION 3.28)
project(MainCMakeList)
message(STATUS "Finite State Machine")

set(CMAKE_CXX_STANDARD 20)
set(BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(CmakeHelpers ${CMAKE_CURRENT_SOURCE_DIR}/cmake_helpers)

include(${CmakeHelpers}/add_subdirectory_recursively.cmake)

message(STATUS "CMAKE_CXX_STANDARD " ${CMAKE_CXX_STANDARD})
message(STATUS "BINARY_DIR " ${BINARY_DIR})

add_subdirectory_recursively(src)
