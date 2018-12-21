cmake_minimum_required(VERSION 2.8.9)
project(async_tcp)
set(CMAKE_BUILD_TYPE Debug)


include_directories(include)
 
file(GLOB SOURCES "src/*.cpp")
 
add_library(async_tcp STATIC ${SOURCES})

set_target_properties(async_tcp PROPERTIES VS_GLOBAL_VcpkgTriplet "x64-windows-static")

install(TARGETS async_tcp DESTINATION lib)