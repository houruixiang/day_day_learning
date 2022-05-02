cmake_minimum_required(VERSION 3.12)
project(CMakeTemplate VERSION 1.0.0 LANGUAGES C CXX DESCRIPTION "A cmake template project")

##--------------------- Version file ---------------------------------------##
configure_file(src/c/cmake_template_version.h.in "${PROJECT_SOURCE_DIR}/src/c/cmake_template_version.h")

# Specified the language standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

##--------------------- Compile Options ------------------------------------##
# Configure compile options
add_compile_options(-Wall -Wextra -pedantic -Werror)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -std=c++17")

# Set build type
# set(CMAKE_BUILD_TYPE Debug)  # Use `cmake -DCMAKE_BUILD_TYPE=Debug` more better
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Compile options for Debug variant
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Compile options for Release variant
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

message(STATUS "Compile options for c: ${CMAKE_C_FLAGS}")
message(STATUS "Compile options for c++: ${CMAKE_CXX_FLAGS}")

##--------------------- Global Macros --------------------------------------##
add_definitions(-DDEBUG -DREAL_COOL_ENGINEER)

##--------------------- Include directories --------------------------------##
include_directories(src/c)

##--------------------- Source files ---------------------------------------##
file(GLOB_RECURSE MATH_LIB_SRC
    src/c/*.c
)

##--------------------- Build target ---------------------------------------##
option(USE_IMPORTED_LIB "Use pre compiled lib" OFF)
if (USE_IMPORTED_LIB)
    # add_library(math STATIC IMPORTED)
    # set_property(TARGET math PROPERTY IMPORTED_LOCATION "./lib/libmath.a")
    find_library(LIB_MATH_DEBUG mathd HINTS "./lib")
    find_library(LIB_MATH_RELEASE math HINTS "./lib")
    add_library(math STATIC IMPORTED GLOBAL)
    set_target_properties(math PROPERTIES
        IMPORTED_LOCATION "${LIB_MATH_RELEASE}"
        IMPORTED_LOCATION_DEBUG "${LIB_MATH_DEBUG}"
        IMPORTED_CONFIGURATIONS "RELEASE;DEBUG"
    )

    add_subdirectory(src/c/nn)
else()
    # Build math lib
    add_subdirectory(src/c/math)
    add_subdirectory(src/c/nn)
endif()

# Merge library
if (APPLE)
    set(MERGE_CMD libtool -static -o)
    add_custom_command(OUTPUT libmerge.a
    COMMAND libtool -static -o libmerge.a $<TARGET_FILE:math> $<TARGET_FILE:nn>
    DEPENDS math nn)
else()
    add_custom_command(OUTPUT libmerge.a
    COMMAND ar crsT libmerge.a $<TARGET_FILE:math> $<TARGET_FILE:nn>
    DEPENDS math nn)
endif()

add_custom_target(_merge ALL DEPENDS libmerge.a)
add_library(merge STATIC IMPORTED GLOBAL)
set_target_properties(merge PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/libmerge.a
)

# Build demo executable
add_executable(demo src/c/main.c)
target_link_libraries(demo PRIVATE merge)

##--------------------- Build unit tests -----------------------------------##
option(CMAKE_TEMPLATE_ENABLE_TEST "Whether to enable unit tests" ON)
if (CMAKE_TEMPLATE_ENABLE_TEST)
    message(STATUS "Unit tests enabled")
    enable_testing()
    add_subdirectory(third_party/googletest-release-1.10.0 EXCLUDE_FROM_ALL)
    include_directories(third_party/googletest-release-1.10.0/googletest/include)

    add_executable(test_add test/c/test_add.cc)
    add_executable(test_minus test/c/test_minus.cc)
    add_executable(test_gtest_demo test/c/test_gtest_demo.cc)
    target_link_libraries(test_add math gtest gtest_main)
    target_link_libraries(test_minus math gtest gtest_main)
    target_link_libraries(test_gtest_demo math gtest gtest_main)

    add_test(NAME test_add COMMAND test_add)
    add_test(NAME test_minus COMMAND test_minus)
    add_test(NAME test_gtest_demo COMMAND test_gtest_demo)
endif()

##--------------------- Install and Package target -------------------------##
# Install
if (NOT USE_IMPORTED_LIB)
    install(TARGETS math nn demo
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            PUBLIC_HEADER DESTINATION include)
    file(GLOB_RECURSE MATH_LIB_HEADERS src/c/math/*.h)
    install(FILES ${MATH_LIB_HEADERS} DESTINATION include/math)
endif()

# Package, These variables should set before including CPack module
set(CPACK_GENERATOR "ZIP")
set(CPACK_SET_DESTDIR ON)  # 支持指定安装目录
set(CPACK_INSTALL_PREFIX "RealCoolEngineer")
include(CPack)
