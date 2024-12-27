cmake_minimum_required(VERSION 3.22.1)

# Set the C++ standard we will use

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_C_COMPILER /usr/bin/gcc-13)
set(CMAKE_CXX_COMPILER /usr/bin/g++-13) 

# Add the path of the cmake files to the CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

project(Astar)

include_directories(
        ${PROJECT_SOURCE_DIR}/inc/ 
)
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/src/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        ) 
# Add project executable

add_executable(Astar ${all_SRCS})