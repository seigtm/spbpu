cmake_minimum_required(VERSION 3.20)

project(
    GolovinskyTest
    VERSION 1.0
    LANGUAGES CXX
)

set(target ${CMAKE_PROJECT_NAME})
set(root ${CMAKE_SOURCE_DIR})

add_executable(${target} ${root}/main.cpp)
set_target_properties(${target}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
