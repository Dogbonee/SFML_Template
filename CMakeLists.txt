cmake_minimum_required(VERSION 3.28)
project(SFML_Template)

set(SFML_DIR)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp
        src/Program.cpp
        src/Program.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)