cmake_minimum_required(VERSION 4.0)

file(GLOB_RECURSE SOURCE "*.cpp" "*.h" "*.hpp")

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 3rd activity game_entity ${CMAKE_CURRENT_SOURCE_DIR})