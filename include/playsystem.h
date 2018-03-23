#ifndef PLAYSYSTEM_H
#define PLAYSYSTEM_H


#include "system.h"
#include "minion.h"
#include "powerup.h"
#include "hero.h"
#include "bullet.h"
#include "gamesetting.h"
#include "controlsystem.h"
#include <SDL.h>

/**
 * @brief  This class sets up the play system.
 *
 * PlaySystem monitors the state of the game.
 * Applied Singleton Design Pattern
 */
class PlaySystem: public System{
public:
    /**
     * @brief Get the PlaySystem instance
     */
    static PlaySystem* getInstance();
    /**
     * @brief Default destructor
     */
    ~PlaySystem();
    /**
     * @brief Initialization
     */
    bool init();
    /**
     * @brief Update
     */
    void update();
    /**
     * @brief Quit play system
     */
    bool quit();
    /**
     * @brief Reset game state
     */
    void reset();
    /**
     * @return true if the player wins
     */
    bool isWin();
    /**
     * @return true if the play loses
     */
    bool isLose();
    // AddScore
    // void addScore();

public:
    bool        isHeroOver();

    bool        isHeroWin();

    bool        isGameOver();

public:
    void        gameOver();


public:
    void        minionsUpdate();

    bool        minionIsLiveUpdate(Minion* m, int i);

    void        minionIsColUpdate(Minion* m);

    void        minionPoseUpdate(Minion* m);

    void        minionPositionUpdate(Minion* m);

    void        minionVelocityUpdate(Minion* m);

public:
    void        heroUpdate();

    void        heroIsColUpdate();

    void        heroPoseUpdate();

    void        heroPositionUpdate();

    void        heroVelocityUpdate();

    void        heroPowerUpdate();

    void        heroFireUpdate();

    void        heroReset();

public:
    void        powerUpUpdate();

    void        powerUpGeneration();

    void        powerUpPoseUpdate(PowerUp* p);

    void        powerUpVelocityUpdate(PowerUp* p);

    void        powerUpPositionUpdate(PowerUp* p);

public:

    void        bulletUpdate();

    void        bulletVelocityUpdate(Bullet* b);

    void        bulletPositionUpdate(Bullet* b);


private:
    /** the only instance */
    static PlaySystem* g_playSystem;
    /**
     * @brief Default Contructor
     */
    PlaySystem();

    bool winState = false; /**< whether the player wins */
    bool loseState = false; /**< whether the player loses */
};

#endif // PLAYSYSTEM_H
