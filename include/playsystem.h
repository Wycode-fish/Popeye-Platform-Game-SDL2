#ifndef PLAYSYSTEM_H
#define PLAYSYSTEM_H


#include "system.h"
#include "minion.h"
#include "powerup.h"
#include "hero.h"
#include "bullet.h"
#include "collectible.h"
#include "gamesetting.h"
#include "controlsystem.h"
#include "tilemapsystem.h"
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

    void initCheckPointList();
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

    bool        isHeroPass();

public:
    void        gameOver();

    void        heroPass();


public:
    void        minionsUpdate();

    bool        minionIsLiveUpdate(Minion* m, int i);

    void        minionIsColUpdate(Minion* m);

    void        minionPoseUpdate(Minion* m);

    void        minionPositionUpdate(Minion* m);

    void        minionVelocityUpdate(Minion* m);

    void        minionsReset();

public:
    void        heroUpdate();

    void        heroIsColUpdate();

    void        heroPoseUpdate();

    void        heroPositionUpdate();

    void        heroVelocityUpdate();

    void        heroPowerUpdate();

    void        heroFireUpdate();

    void        heroCheckPointUpdate();

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

    void        bulletPoseUpdate(Bullet* b);

public:

    void        setRecentCheckPoint(Vector2D cp);

    Vector2D    getRecentCheckPoint();

    vector<Vector2D> getCheckedPointList();

public:

    void        collectibleUpdate();

    void        collectiblePoseUpdate(Collectible* p);

    void        collectibleVelocityUpdate(Collectible* p);

    void        collectiblePositionUpdate(Collectible* p);





private:
    /** the only instance */
    static PlaySystem* g_playSystem;
    /**
     * @brief Default Contructor
     */
    PlaySystem();

    Vector2D    recentCheckPoint = Vector2D(0.0f, 0.0f);

    vector<Vector2D> checkedPointList;

    vector<Vector2D> uncheckedPointList;


    bool winState = false; /**< whether the player wins */
    bool loseState = false; /**< whether the player loses */
};

#endif // PLAYSYSTEM_H
