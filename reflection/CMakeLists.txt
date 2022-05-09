cmake_minimum_required(VERSION 3.0.0)
project(refleact VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
# include(CTest)
# enable_testing()
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(refleact_StaticRefl StaticRefl.cpp)
add_executable(refleact_StaticRefl_TupleImpl StaticRefl_TupleImpl.cpp)


# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
