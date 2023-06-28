cmake_minimum_required(VERSION 3.23)
project(ingressGateway)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurl")


add_executable(ingressGateway ingressGateway_main.cpp utils/time_utils.cpp Quote.cpp Spot.cpp utils/curl_utils.cpp)
#add_executable(ingressGatewayAnotherMain anotherMain.cpp)
target_include_directories(ingressGateway PUBLIC ${CMAKE_CURRENT_LIST_DIR})


target_include_directories(ingressGateway PUBLIC utils)

target_link_libraries(ingressGateway curl)
include_directories("/utils")

