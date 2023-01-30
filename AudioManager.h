//
// Created by alber on 26/01/2023.
//

#ifndef ELABORATO_AUDIOMANAGER_H
#define ELABORATO_AUDIOMANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <vector>
#include <map>
#include <iterator>

#include "GameException.h"

class AudioManager {
private:
    //music
    std::map<std::string, sf::Music> playlist;
    std::map<std::string, sf::Music>::iterator songsIter;
    const float backgroundVolume = 15;

    //sound effects
    struct SoundEffect {
        sf::SoundBuffer soundBuffer;
        sf::Sound sound;
    };
    std::map<std::string, SoundEffect> soundEffects;

public:
    AudioManager();

    void loadMusic(std::string name, std::string fileName);

    void loadSound(std::string name, std::string fileName);

    void updateMusicStatus();

    void playSound(std::string name);

    void stopSound(std::string name);

    void startPlaylist();

    void playMusicFromPlaylist(std::string name);

    void stopMusicFromPlaylist(std::string name);

    void pauseMusicFromPlaylist(std::string name);


};


#endif //ELABORATO_AUDIOMANAGER_H
