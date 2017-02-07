cmake_minimum_required(VERSION 3.6)
project(FlipCard)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp card.h deck.h)
add_executable(FlipCard ${SOURCE_FILES})