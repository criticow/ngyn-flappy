cmake_minimum_required(VERSION 3.31.6)

set(CMAKE_CXX_STANDARD 20)

set(NGYN_BUILD_TESTS OFF)
set(NGYN_BUILD_EXAMPLES OFF)

project(FlappyDog)

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/game.cpp
  src/dog.cpp
  src/obstacle.cpp
  src/obstacle_manager.cpp
  src/ui.cpp

  resources.rc
)

target_link_libraries(${PROJECT_NAME} PRIVATE ngyn)

add_subdirectory(deps/ngyn)

set(DATA_DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/data)

add_custom_target(
  copy_data ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_LIST_DIR}/data ${DATA_DESTINATION}
)

add_dependencies(${PROJECT_NAME} copy_data)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(${PROJECT_NAME} PRIVATE -NDEBUG)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
endif()