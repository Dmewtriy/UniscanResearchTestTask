cmake_minimum_required(VERSION 3.20)
project(Packet)

set(SOURCE_LIB Packet.cpp) 
add_library(LIB_Packet STATIC ${SOURCE_LIB})