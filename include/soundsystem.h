#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <SDL_mixer.h>
#include "system.h"
#include "gamesetting.h"
#include "resourcemanager.h"
// Singleton Design Pattern

enum CHANNEL{
    BACKGROUND_CHANNEL = 0,
    WIN_CHANNEL = 1,
    LOSE_CHANNEL = 2,
    COLLISION_CHANNEL = 3,
    POWERUP_CHANNEL = 4,
    FIRE_CHANNEL = 5,
    OVER_CHANNEL = 6,
    PASS_CHANNEL = 7,
    CHECK_POINT_CHANNEL = 8,
    JUMP_CHANNEL = 9
};

class SoundSystem : public System{
public:
    static SoundSystem* getInstance();
    ~SoundSystem();
    bool init();
    void update();
    bool quit();

    void playWinSound();
    void playLoseSound();
    void playCollisionSound();
    void playPowerUpSound();
    void playFireSound();
    void playOverSound();
    void playPassSound();
    void playJumpSound();
    void playCollectibleSound();
    void playCheckPointSound();
    void playCurrentLevelBackground();
    void playKickSound();
    void pauseCurrentLevelBackground();
    void resumeCurrentLevelBackground();
    void playMainMenuBackground();
    void start();
private:
    static SoundSystem* gSoundSystem;
    SoundSystem();
    int currentLevel = 1;
};

#endif // SOUNDSYSTEM_H
