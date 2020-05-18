cmake_minimum_required(VERSION 3.17)
project(oop)

add_executable(oop main.cpp)

add_library(
	files
	functions.h
	functions.cpp
	struct.h
	vector.h
)

target_link_libraries(oop files)