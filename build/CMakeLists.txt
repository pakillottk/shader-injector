cmake_minimum_required(VERSION 3.10)

# set the project name
project(shader-injector)

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin )

# add the executable
add_executable(
    shader-injector 
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Args/ArgsParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp
)