cmake_minimum_required(VERSION 3.20)
project(testTask)

set(SOURCE_EXE main.cpp)

include_directories(Packet) 

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

add_subdirectory(Packet)

target_link_libraries(${PROJECT_NAME} LIB_Packet)
