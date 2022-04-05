set(headers
        ../include/draw/draw.h
        )
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(draw draw.cc ${headers})
target_include_directories(draw PUBLIC ../include)
target_link_libraries(draw ${OpenCV_LIBS})