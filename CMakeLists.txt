cmake_minimum_required(VERSION 3.28)
project(GameOfLife)

set(SFML_DIR C:/StudentFiles/Student/SFML-2.6.1/lib/cmake/SFML)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES src/main.cpp
        src/Program.cpp
        src/Program.h
        src/PodCollection.cpp
        src/PodCollection.h
        src/Vector2Hash.cpp
        src/Vector2Hash.h
        src/Button.cpp
        src/Button.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set(SFML_STATIC_LIBRARIES true)


find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)