add_executable(draw main.cc)
target_link_libraries(draw PRIVATE libdraw)
install(TARGETS draw DESTINATION bin)

