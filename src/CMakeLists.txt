set(headers
        ../include/draw/draw.h
        )
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(libdraw draw.cc ${headers})
target_include_directories(libdraw PUBLIC ../include)
target_link_libraries(libdraw ${OpenCV_LIBS})
set_target_properties(libdraw PROPERTIES PUBLIC_HEADER "../include/draw/draw.h")
INSTALL(TARGETS libdraw
        LIBRARY DESTINATION /usr/lib
        PUBLIC_HEADER DESTINATION /usr/include
	ARCHIVE DESTINATION /usr/lib
)
