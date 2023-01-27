cmake_minimum_required(VERSION 3.20)
project(Elaborato)

set(CMAKE_CXX_STANDARD 11)
add_executable(Elaborato main.cpp GameCharacter.cpp GameCharacter.h Game.cpp Game.h GameState.h GameState.cpp MenuState.cpp MenuState.h PlayState.cpp PlayState.h TextureManager.cpp TextureManager.h ArenaMap.cpp ArenaMap.h PosEntity.h GameException.cpp GameException.h Spawner.cpp Spawner.h Bonus.cpp Bonus.h Mike.cpp Mike.h Animation.cpp Animation.h Gui.cpp Gui.h Weapon.cpp Weapon.h Handgun.cpp Handgun.h AssaultRifle.cpp AssaultRifle.h Shotgun.cpp Shotgun.h Bullet.cpp Bullet.h ShotgunBullet.cpp ShotgunBullet.h PosEntity.cpp NewWeapon.cpp NewWeapon.h Dice.cpp Dice.h Coin.cpp Coin.h Zombie.cpp Zombie.h Nuke.cpp Nuke.h Ammunition.cpp Ammunition.h LifePoints.cpp LifePoints.h ProtectionBubble.cpp ProtectionBubble.h Armor.cpp Armor.h IncreasedWeaponDamage.cpp IncreasedWeaponDamage.h PauseState.cpp PauseState.h Warrior.cpp Warrior.h Kamikaze.cpp Kamikaze.h Boss.cpp Boss.h AI.cpp AI.h Node.cpp Node.h Enemy.cpp Enemy.h Archer.cpp Archer.h Bow.cpp Bow.h AchievementManager.cpp AchievementManager.h Subject.h Observer.h Achievement.cpp Achievement.h AchievementState.cpp AchievementState.h Scepter.cpp Scepter.h AudioManager.cpp AudioManager.h)
#SFML
if (WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)

    #file(COPY "c:/mingw32/bin/libgcc_s_dw2-1.dll" DESTINATION ${CMAKE_BINARY_DIR})#richiesta per le eccezioni
    file(GLOB MINGW_DEP_DLLS "C:/mingw32/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})


    set(SFML_DIR C:/SFML/lib/cmake/SFML) #SFML Windows Directory
    file(COPY "${SFML_DIR}/../../../bin/openal32.dll " DESTINATION ${CMAKE_BINARY_DIR}) #audio dll
    find_package(SFML COMPONENTS system window graphics audio network REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(Elaborato sfml-system sfml-window sfml-audio sfml-graphics sfml-network)
        file(GLOB BINARY_DEP_DLLS "${SFML_DIR}/../../../bin/*.dll ")
        file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    endif ()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set (MACOSX TRUE)
    if (false)
        set(SFML_DIR /usr/local/Cellar/sfml/) #SFML Macos Directory
    endif ()
    find_package (SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries (Elaborato sfml-system sfml-window sfml-audio sfml-graphics sfml-network)
    endif()
endif()
#Google Test
file(COPY "./res" DESTINATION ${CMAKE_BINARY_DIR})
add_subdirectory(test)
