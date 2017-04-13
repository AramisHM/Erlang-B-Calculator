cmake_minimum_required (VERSION 2.8.11)
PROJECT (extended_erlang_b)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(./include)

# executables directory

if(MSVC)
	add_executable (Erlang_estendido_B main.cpp ./resources.rc) #with custom executable icon
	
else()
	add_executable (Erlang_estendido_B main.cpp)
endif()
