cmake_minimum_required(VERSION 3.10)

add_library(lb_common INTERFACE)

target_include_directories(lb_common INTERFACE lb_common)

add_library(lb_filesystem INTERFACE)

target_include_directories(lb_filesystem INTERFACE lb_filesystem)

# only mac requires boost for filesystem
if(APPLE)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_DEBUG OFF)
    set(Boost_USE_STATIC_LIBS ON)
    if(WIN32)
        set(Boost_USE_STATIC_RUNTIME ON)
        add_definitions( -DBOOST_ALL_NO_LIB ) # disable auto linking
    endif()
    find_package(Boost 1.60.0 REQUIRED COMPONENTS system filesystem)

    target_include_directories(lb_filesystem INTERFACE ${Boost_INCLUDE_DIRS})
    target_link_libraries(lb_filesystem INTERFACE ${Boost_LIBRARIES})
else()
    if(UNIX AND NOT APPLE AND NOT EMSCRIPTEN)
        target_link_libraries(lb_filesystem INTERFACE stdc++fs)
    endif()
endif()
