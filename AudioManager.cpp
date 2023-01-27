//
// Created by alber on 26/01/2023.
//

#include "AudioManager.h"

AudioManager::AudioManager() = default;

void AudioManager::updateMusicStatus() {
    //next song

    if ((!playlist.empty()) && (songsIter->second.getStatus() == sf::SoundSource::Stopped)) {
        songsIter++;
        if (songsIter == playlist.end())
            songsIter = playlist.begin();
        //restart from playlist begin
        songsIter->second.stop();
        songsIter->second.play();
        //FIXME check if the volume must be set
    }
}

void AudioManager::loadMusic(std::string name, std::string fileName) {
    // Load music
    try {
        if (!this->playlist[name].openFromFile(fileName))
            throw GameException("Error opening music file", fileName, false);
    } catch (GameException &e) {
        exit(1); //close all
    }
}

void AudioManager::loadSound(std::string name, std::string fileName) {
    // Load sound
    try {
        if (!this->soundEffects[name].soundBuffer.loadFromFile(fileName))
            throw GameException("Error opening music file", fileName, false);
    } catch (GameException &e) {
        exit(1); //close all
    }

    //set buffer into a sound
    soundEffects[name].sound.setBuffer(soundEffects[name].soundBuffer);
}

void AudioManager::playSound(std::string name) {
    if (!soundEffects.empty())
        soundEffects[name].sound.play();
}

void AudioManager::stopSound(std::string name) {
    if (!soundEffects.empty())
        soundEffects[name].sound.stop();
}

void AudioManager::startPlaylist() {
    //play first playlist song
    if (!playlist.empty()) {
        playlist.begin()->second.play();
        songsIter = playlist.begin();
        songsIter->second.setVolume(backgroundVolume);
        //songsIter->second.setPlayingOffset(sf::seconds(165));
    }
}

void AudioManager::playMusicFromPlaylist(std::string name) {
    if (!playlist.empty())
        playlist[name].play();
}

void AudioManager::stopMusicFromPlaylist(std::string name) {
    if (!playlist.empty())
        playlist[name].stop();
}

void AudioManager::pauseMusicFromPlaylist(std::string name) {
    if (!playlist.empty())
        playlist[name].pause();
}
