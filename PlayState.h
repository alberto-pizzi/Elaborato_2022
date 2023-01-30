//
// Created by alber on 25/10/2022.
//

#ifndef ELABORATO_PLAYSTATE_H
#define ELABORATO_PLAYSTATE_H

#include <cstdlib>
#include <ctime>
#include <cmath>

#include "GameState.h"
#include "ArenaMap.h"
#include "Spawner.h"
#include "Mike.h"
#include "TextureManager.h"
#include "Gui.h"
#include "PauseState.h"
#include "AudioManager.h"

//WARNING: for adding other Map, you must updateNotCyclicalAnimation nMap/loadMap and enum in ArenaMap.h
const int nMap = 1;

class PlayState : public GameState {
private:
    enum nEnemies {
        baseNumberForNormalRounds = 15,
        incrementableNumber = 5,
        stabilizationRound = 50,
        initialBossFrequency = 5,
        baseNumberForBossRounds = 5,
        percentageIncrement = 5,
    };

    sf::View gameView;
    sf::View guiView;
    std::shared_ptr<ArenaMap> arenaMap;
    std::unique_ptr<Spawner> spawner;
    std::unique_ptr<Mike> mike;

    sf::Clock frame_clock;

    //mouse input positioning
    sf::Vector2i localPosition;
    sf::Vector2f worldPos;
    sf::Sprite viewfinderSprite;

    //texture managers
    TextureManager weaponsTextures;
    TextureManager guiTextures;
    TextureManager charactersTextures;
    TextureManager bonusesTextures;

    //game management
    struct EnemySpawnData {
        unsigned int numberOfEnemies;
        float typePercentage;
    };
    unsigned int bossRoundFrequency = initialBossFrequency;
    unsigned int round;
    unsigned int remainEnemies;
    unsigned int remainBosses;
    unsigned int countVariableEnemiesForNormalRound = 0;
    unsigned int countVariableEnemiesForBossRound = 0;
    const float damageIncrement = 0.25;
    sf::Clock roundSleepClock;
    sf::Clock roundClock;
    sf::Time afterRoundSleepTime = sf::seconds(3); //FIXME 20
    const sf::Time firstRoundStartingTime = sf::seconds(3); //FIXME 10
    bool firstSpawnDone = false;
    bool endRoundCountStarted = false;
    Dice randomPercentageDice;
    std::map<int, EnemySpawnData> totEnemiesForType; //not bosses

    //pause
    bool isPaused = false;

    //game over
    bool gameOver = false;
    bool startedGameOver = false;
    sf::Clock gameOverClock;
    sf::Time gameOverTime = sf::seconds(5);

    //auto-save progress
    sf::Clock saveClock;
    sf::Time saveGap = sf::seconds(5 * 60); //every 5 minutes save achievement progress to a file

    //audio
    AudioManager audioManager;
public:
    explicit PlayState(Game *game);

    virtual ~PlayState();

    const std::shared_ptr<ArenaMap> &getArenaMap() const;

    void draw(float dt) const override;

    void update(float dt) override;

    void handleInput() override;

    int whichMap();

    void loadTextures();

    sf::Vector2f normalizedViewfinderPos(const sf::Vector2f &viewfinderPos, const GameCharacter &character);

    void updateBonuses(float dt);

    void updateEnemies(float dt);

    void updateBosses(float dt);

    void initRound();

    void spawnEachTypeOfEnemies();

    bool isRoundEnded() const;

    bool isInteger(float n) const;

    void checkAndUpdateRound();

    void updateViewfinderColor(const GameCharacter &enemy);

    void checkMikeDead(float dt);

    float calculateEnemyHitProbability(int enemyType) const;

    float calculateDamageMultiplierPerRound() const;

    void spawnBonuses();

    void autoSaveProgress();

    void loadAudio();


};

#endif //ELABORATO_PLAYSTATE_H
