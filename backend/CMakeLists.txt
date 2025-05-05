cmake_minimum_required(VERSION 3.10)

project(steganography-server)

set(CMAKE_CXX_STANDARD 17)

# Найти Boost и его компонент для многозадачности (thread)
find_package(Boost REQUIRED COMPONENTS thread)

# Проверяем, что Boost был найден
if(Boost_FOUND)
    message(STATUS "Boost found at ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Создаем исполнимый файл
add_executable(steganography-server main.cpp)

# Линковка с Boost и pthread
target_link_libraries(steganography-server Boost::thread pthread)