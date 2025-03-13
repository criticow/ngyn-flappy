cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CXX_STANDARD 20)

set(NGYN_BUILD_TESTS OFF)
set(NGYN_BUILD_EXAMPLES OFF)

project(flappy)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/game.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ngyn)

add_subdirectory(deps/ngyn)