cmake_minimum_required(VERSION 3.13.4)
project(DaikinTestProject)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# add_executable(DaikinTestRun main.cpp TemperatureControl.cpp)
add_executable(DaikinGTestRun TemperatureControlTest.cpp TemperatureControl.cpp)

target_link_libraries(DaikinGTestRun pthread ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

