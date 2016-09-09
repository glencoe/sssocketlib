add_library(sssocketlib tcpsocket.hpp)
add_executable(main main.cpp)
target_link_libraries(main sssocketlib)
