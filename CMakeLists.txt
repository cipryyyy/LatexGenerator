cmake_minimum_required(VERSION 3.10)

project(LatexGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(LatexGenerator 
    interfaces/converter.cpp
    LatexGenerator/Latex.cpp
)

target_include_directories(LatexGenerator PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/LatexGenerator
)
