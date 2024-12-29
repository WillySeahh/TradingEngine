cmake_minimum_required(VERSION 3.23)
project(orderbookv2)

set(CMAKE_CXX_STANDARD 20)

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.45.0 COMPONENTS *boost libraries here*)
#
#FIND_PACKAGE(Boost)
#IF (Boost_FOUND)
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#    ADD_DEFINITIONS( "-DHAS_BOOST" )
#ENDIF()
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}) # need to do this else cannot find text file


add_executable(orderbookv2 src/orderbookv2_main.cpp src/helpers.cpp src/orderbook.cpp)

