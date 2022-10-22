cmake_minimum_required(VERSION 3.20)
project(Elaborato)

set(CMAKE_CXX_STANDARD 11)

add_executable(Elaborato main.cpp GameCharacter.cpp GameCharacter.h)
#SMFL
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML) #SFML Directory
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
include_directories(C:/SFML/include) #SFML Directory
target_link_libraries(Elaborato sfml-system sfml-window sfml-graphics sfml-audio)

#Google Test
add_subdirectory(test)
set(SOURCE_FILES GameCharacter.cpp GameCharacter.h)
add_library(core ${SOURCE_FILES})
target_link_libraries(Elaborato core)