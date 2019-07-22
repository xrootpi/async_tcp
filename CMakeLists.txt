cmake_minimum_required(VERSION 2.8.9)
project(async-tcp)

include_directories(include)


file(GLOB SOURCES "src/*.cpp")
 
add_library(async-tcp ${SOURCES})
find_package(Boost REQUIRED)


target_link_libraries (async-tcp pthread)
target_link_libraries (async-tcp ${Boost_LIBRARIES})

target_include_directories(async-tcp PRIVATE  ${Boost_INCLUDE_DIRS})
install(TARGETS async-tcp DESTINATION lib)
