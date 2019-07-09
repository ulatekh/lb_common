cmake_minimum_required(VERSION 3.10)

add_library(lb_common INTERFACE)

target_include_directories(lb_common INTERFACE lb_common)

add_library(lb_filesystem INTERFACE)

target_include_directories(lb_common INTERFACE lb_filesystem)