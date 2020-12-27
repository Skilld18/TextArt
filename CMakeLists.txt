cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
project(draw)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wsign-conversion)
find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)


