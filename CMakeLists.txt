cmake_minimum_required(VERSION 3.19)

project(ConfigParser)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-g -O2 -Wall -Werror -Wno-unused)

include_directories(./)

file(GLOB_RECURSE SOURCES "./utility/*.cpp")

add_executable(iniParser ${SOURCES} iniParser.cpp)
add_executable(jsonParser ${SOURCES} jsonParser.cpp)
add_executable(xmlParser ${SOURCES} xmlParser.cpp)


