cmake_minimum_required(VERSION 3.23)
project(threads)

set(CMAKE_CXX_STANDARD 17)

add_executable(threads_example threads_example.cpp thread_utils.hpp threads_example.cpp)



