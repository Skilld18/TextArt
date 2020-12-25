set(headers
    ../include/draw/draw.h
)

add_library(draw draw.cc ${headers})
target_include_directories(draw PUBLIC ../include)
