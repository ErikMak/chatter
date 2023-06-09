add_executable(chatter-test chatter.cpp)
target_link_libraries(chatter-test server_lib socket_lib tcpclient_lib)
add_test(chatter-test chatter-test)