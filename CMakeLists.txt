cmake_minimum_required(VERSION 3.23)
project (TradingEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(TradingEngine main.cpp)

#add_executable(orderbook_main orderbook/orderbook_main.cpp)

add_subdirectory(orderbook)

