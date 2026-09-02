cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    src/*.cc
)

add_executable(app ${SOURCES})

target_include_directories(app PRIVATE include)

target_compile_options(app PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

target_link_options(app PRIVATE
    $<$<CONFIG:Debug>:-fsanitize=address>
)
