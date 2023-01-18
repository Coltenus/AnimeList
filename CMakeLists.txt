cmake_minimum_required(VERSION 3.24)
project(AnimeList)

set(CMAKE_CXX_STANDARD 20)

add_executable(AnimeList main.cpp src/common.h src/InputField.cpp src/InputField.h src/Button.cpp src/Button.h src/ListItem.cpp src/ListItem.h)

find_package(raylib CONFIG REQUIRED)
target_include_directories(AnimeList PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(AnimeList PRIVATE ${raylib_LIBRARIES})