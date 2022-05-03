cmake_minimum_required(VERSION 3.17)

project(reliab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE DEBUG)

add_library(reliab INTERFACE)
target_include_directories(reliab INTERFACE "include/")


add_executable(main main.cpp)
# target_link_libraries(main PRIVATE reliab)

