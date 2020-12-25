cmake_minimum_required(VERSION 3.16)
project(draw)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)
find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(tests)


