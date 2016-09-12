add_library(sssocketlib tcpsocket.cpp socketexception.cpp C/socket.c)
add_executable(main main.cpp)
target_link_libraries(main sssocketlib)
