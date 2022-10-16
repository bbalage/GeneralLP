cmake_minimum_required(VERSION 3.16)

project(GeneralLP VERSION 1.0 LANGUAGES CXX)

add_compile_definitions(PROJECT_DIR=\"${PROJECT_SOURCE_DIR}\")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# OpenCV might litter the command line with warnings... 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -fsanitize=address,leak,undefined -m64") #-Wlifetime?
# set(CMAKE_CXX_FLAGS, "-f-sanitize=leak -m64 -O3")

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
