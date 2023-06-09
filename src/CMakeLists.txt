cmake_minimum_required(VERSION 3.0)
project(chatter)

enable_testing()

# Флаги компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wfatal-errors")

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(tests)
# Создание исполняемого файла
add_executable(chatter-server server.cpp)
add_executable(chatter-client client.cpp)
# Линковка 
set(SOURCES view_lib storage_lib controller_lib)

target_link_libraries(chatter-server server_lib)
target_link_libraries(chatter-server socket_lib)
target_link_libraries(chatter-client ${SOURCES})