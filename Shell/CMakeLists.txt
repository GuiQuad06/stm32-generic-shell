cmake_minimum_required(VERSION 3.22)

add_library(shell STATIC shell.c)

target_include_directories(shell PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
