cmake_minimum_required(VERSION 3.11)
#set(CMAKE_C_COMPILER /usr/local/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/local/bin/g++)
project(HR_Tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SRC_LIST "src/*.cpp" "src/*.h")
add_executable(hr_tree ${SRC_LIST})