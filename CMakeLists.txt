cmake_minimum_required(VERSION 2.8.9)
project(async_tcp)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_library(async_tcp STATIC ${SOURCES})

install(TARGETS async_tcp DESTINATION lib)