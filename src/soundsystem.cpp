#include "../include/soundsystem.h"

SoundSystem* SoundSystem::gSoundSystem = NULL;

SoundSystem* SoundSystem::getInstance(){
    if ( !gSoundSystem )
        gSoundSystem = new SoundSystem();
    return gSoundSystem;
}

SoundSystem::SoundSystem(){
    // Now do nothing
}

SoundSystem::~SoundSystem(){
    if (gSoundSystem != NULL)
        delete[] gSoundSystem;
}

bool SoundSystem::init(){
    bool success = true;
    currentLevel = GameSetting::getInstance()->getLevel();
//    playMainMenuBackground();
    return success;
}

void SoundSystem::update(){
    int level = GameSetting::getInstance()->getLevel();
    if (level != currentLevel){
        currentLevel = level;
        playCurrentLevelBackground();
    }
}

bool SoundSystem::quit(){
    bool success = true;
    return success;
}

void SoundSystem::playWinSound(){
    //Mix_Pause(BACKGROUND_CHANNEL);
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("win_sound"), 0);
}

void SoundSystem::playLoseSound(){
    //Mix_Pause(BACKGROUND_CHANNEL);
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("lose_sound"), 0);
}

void SoundSystem::playCollisionSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("collision_sound"), 0);
}

void SoundSystem::playPowerUpSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("powerup_sound"), 0);
}

void SoundSystem::playFireSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("fire_sound"), 0);
}
void SoundSystem::playOverSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("over_sound"), 0);
}

void SoundSystem::playPassSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("pass_sound"), 0);
}

void SoundSystem::playCheckPointSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("check_point_sound"), 0);
}

void SoundSystem::playCurrentLevelBackground(){
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4.0);
    switch (currentLevel) {
    case 1:{
        Mix_PlayMusic( ResourceManager::getInstance()->getMixMusicResource("snowscene_background"), -1 );
        break;
    }
    case 2:{
        Mix_PlayMusic( ResourceManager::getInstance()->getMixMusicResource("kungfu_background"), -1 );
        break;
    }
    case 3:{
        Mix_PlayMusic( ResourceManager::getInstance()->getMixMusicResource("oldcastle_background"), -1 );
        break;
    }
    default:
        break;
    }
}

void SoundSystem::start(){
    currentLevel = 1;
    playCurrentLevelBackground();
}

void SoundSystem::playMainMenuBackground(){
    Mix_VolumeMusic(MIX_MAX_VOLUME / 4.0);
    Mix_PlayMusic( ResourceManager::getInstance()->getMixMusicResource("mainmenu_background"), -1 );
}

void SoundSystem::playJumpSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("jump_sound"), 0);
}

void SoundSystem::playCollectibleSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("collectible_sound"), 0);
}

void SoundSystem::pauseCurrentLevelBackground(){
    Mix_Pause(-1);
}
void SoundSystem::resumeCurrentLevelBackground(){
    Mix_Resume(-1);
}

void SoundSystem::playKickSound(){
    Mix_PlayChannel(-1, ResourceManager::getInstance()->getChunkResource("kick_sound"), 0);
}


