add_library(tcpclient_lib SHARED TCPClient.cpp ${PROJECT_SOURCE_DIR}/server/tcpsocket.cpp)
add_library(storage_lib SHARED Subject.cpp Storage.cpp)