cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_FLAGS -std=c++11)
# add_definitions(-std=c++11)
project (Tutorial)
set (SOURCES
src/main.cc
src/effective_cpp/item35/item35.cpp
src/effective_modern_cpp/chapter06.cpp
)
add_executable(Tutorial ${SOURCES})
target_link_libraries(Tutorial pthread)
