cmake_minimum_required(VERSION 3.20)
project(runTests)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp GameCharacterTest.cpp ../GameCharacter.cpp ../GameCharacter.h ../Game.cpp ../Game.h ../GameState.h ../GameState.cpp ../MenuState.cpp ../MenuState.h ../PlayState.cpp ../PlayState.h ../TextureManager.cpp ../TextureManager.h ../ArenaMap.cpp ../ArenaMap.h ../PosEntity.h ../GameException.cpp ../GameException.h ../Spawner.cpp ../Spawner.h ../Bonus.cpp ../Bonus.h ../Mike.cpp ../Mike.h ../Animation.cpp ../Animation.h MenuTest.cpp)
add_executable(runTests ${TEST_SOURCE_FILES})

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(SFML_DIR C:/SFML/lib/cmake/SFML) #SFML Windows Directory
    find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(runTests sfml-system sfml-window sfml-audio sfml-graphics sfml-network)
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
    if (false)
        set(SFML_DIR /usr/local/Cellar/sfml/) #SFML Macos Directory
    endif ()
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(runTests sfml-system sfml-window sfml-audio sfml-graphics sfml-network)
    endif ()
endif ()

target_link_libraries(runTests gtest gtest_main)