cmake_minimum_required(VERSION 2.8.9)
project(async_tcp)

include_directories(include)


file(GLOB SOURCES "src/*.cpp")
 
add_library(async_tcp STATIC ${SOURCES})
find_package(Boost REQUIRED)
target_include_directories(async_tcp  PRIVATE ${Boost_INCLUDE_DIRS})
install(TARGETS async_tcp DESTINATION lib)