cmake_minimum_required(VERSION 3.20)
project(runTests)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp GameCharacterTest.cpp ../GameCharacter.cpp ../GameCharacter.h ../Game.cpp ../Game.h ../GameState.h ../GameState.cpp ../MenuState.cpp ../MenuState.h ../PlayState.cpp ../PlayState.h ../TextureManager.cpp ../TextureManager.h ../ArenaMap.cpp ../ArenaMap.h ../PosEntity.h ../GameException.cpp ../GameException.h ../Spawner.cpp ../Spawner.h ../Bonus.cpp ../Bonus.h ../Mike.cpp ../Mike.h ../Animation.cpp ../Animation.h StateTest.cpp ../Gui.h ../Gui.cpp ../Weapon.h ../Weapon.cpp ../Bullet.h ../Bullet.cpp ../Handgun.h ../Handgun.cpp GameCharacterFixture.cpp GameCharacterFixture.h StateFixture.cpp StateFixture.h ../ShotgunBullet.cpp ../ShotgunBullet.h ../PosEntity.cpp ArenaMapFixture.cpp ArenaMapFixture.h ArenaMapTest.cpp ../Dice.cpp ../Dice.h ../NewWeapon.h ../NewWeapon.cpp ../AssaultRifle.h ../AssaultRifle.cpp ../Shotgun.h ../Shotgun.cpp ../Coin.cpp ../Coin.h ../Zombie.cpp ../Zombie.h ../Nuke.cpp ../Nuke.h ../Ammunition.cpp ../Ammunition.h ../LifePoints.cpp ../LifePoints.h ../ProtectionBubble.cpp ../ProtectionBubble.h ../Armor.cpp ../Armor.h ../IncreasedWeaponDamage.cpp ../IncreasedWeaponDamage.h ../PauseState.cpp ../PauseState.h ../Warrior.cpp ../Warrior.h ../Kamikaze.cpp ../Kamikaze.h ../Boss.cpp ../Boss.h ../Node.cpp ../Node.h ../Enemy.cpp ../Enemy.h ../Archer.cpp ../Archer.h ../Bow.cpp ../Bow.h ../AchievementManager.cpp ../AchievementManager.h ../Subject.h ../Observer.h ../AchievementType.cpp ../AchievementType.h ../AchievementState.cpp ../AchievementState.h ../Scepter.cpp ../Scepter.h ../AudioManager.cpp ../AudioManager.h ../AI.cpp ../AI.h SpawnerFixture.cpp SpawnerFixture.h SpawnerTest.cpp AchievementFixture.cpp AchievementFixture.h AchivementTest.cpp)
add_executable(runTests ${TEST_SOURCE_FILES})

if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)

    file(GLOB MINGW_DEP_DLLS "C:/mingw32/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR}/test/)

    set(SFML_DIR C:/SFML/lib/cmake/SFML) #SFML Windows Directory
    file(COPY "${SFML_DIR}/../../../bin/openal32.dll " DESTINATION ${CMAKE_BINARY_DIR}/test/) #audio dll
    find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(runTests sfml-system sfml-window sfml-audio sfml-graphics sfml-network)
        file(GLOB BINARY_DEP_DLLS "${SFML_DIR}/../../../bin/*.dll ")
        file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR}/test/)
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

file(COPY "../res" DESTINATION "${CMAKE_BINARY_DIR}/test/")
target_link_libraries(runTests gtest gtest_main)