cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(GNSS_RECEIVER_BUILD_EXAMPLES "Set to ON to build example projects" OFF)

project(GnssReceiver)

add_subdirectory(src)

if(GNSS_RECEIVER_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()