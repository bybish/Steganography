cmake_minimum_required(VERSION 3.10)
project(steganography-server)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

add_executable(steganography-server main.cpp)

target_link_libraries(steganography-server PRIVATE Boost::boost pthread)