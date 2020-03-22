cmake_minimum_required(VERSION 3.2)
project(SimpleOpus)

set(CMAKE_CXX_STANDARD 17)

add_library(SimpleOpus SimpleOpus.cpp SimpleOpus.hpp)
target_link_libraries(SimpleOpus opus)

add_executable(SimpleOpus_Test test.cpp)
target_link_libraries(SimpleOpus_Test SimpleOpus)

add_executable(SimpleOpus_Test2 test2.cpp)
target_link_libraries(SimpleOpus_Test2 SimpleOpus)