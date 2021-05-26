# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.

cmake_minimum_required(VERSION 3.1...3.15)
project(Proyecto1 VERSION 1.0)

find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

if(CGAL_Qt5_FOUND)
add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
endif()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB SOURCES_EXE "src/*.cpp")
file(GLOB TESTS_EXE "test/*.cpp" "src/Punto.cpp")
add_compile_options("-W" "-Wall" "-pedantic")
add_executable(Proyecto1 ${SOURCES_EXE})
add_executable(Tests ${TESTS_EXE})


if(CGAL_Qt5_FOUND)
  target_link_libraries(Proyecto1 PUBLIC CGAL::CGAL_Qt5)
  target_link_libraries(Tests PUBLIC CGAL::CGAL_Qt5 ${GTEST_LIBRARIES} pthread)
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
