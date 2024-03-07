cmake_minimum_required(VERSION 3.22.1)
project(cmilan)

# Set C++ standard and compile options.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -O2") # -Werror

# Specify source and header directories.
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)

# Get all the sources.
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

# Create the executable target.
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Specify include directories.
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${HEADER_DIR})

# Set additional target properties.
set_target_properties(
  ${CMAKE_PROJECT_NAME}
  PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD}
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)

# Export compile commands for external tooling.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
