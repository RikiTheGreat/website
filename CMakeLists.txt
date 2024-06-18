cmake_minimum_required(VERSION 3.29)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(website)
set(CMAKE_CXX_STANDARD 26)

find_package(boost_asio REQUIRED CONFIG)
find_package(Boost REQUIRED COMPONENTS beast)

add_subdirectory(src)
