cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
project(draw VERSION 2.0)

set(SOURCE_FILES
src/utils.cc
src/draw.cc
example/main.cc)

add_executable( ${PROJECT_NAME} ${SOURCE_FILES} )
target_link_libraries(draw ${OpenCV_LIBS} )
include_directories(include)