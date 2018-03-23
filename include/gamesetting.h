#ifndef GAMESETTING_H
#define GAMESETTING_H


#include <vector>
#include <iostream>
#include <fstream>
#include "vector2d.h"
#include "constants.h"
#include "hero.h"
#include "minion.h"
#include "powerup.h"
#include "bullet.h"
#include "system.h"
#include <map>
#include <stddef.h>
#include <string>

using namespace std;
/**
 * @brief This class defines the game setting.
 *
 * Applied Singleton Design Pattern
 */
class GameSetting: public System{
public:
    /**
     * @brief Get the only distance
     */
    static GameSetting* getInstance();
    //static map<string, int> ControlSchemes;

    enum ControlSchemes { /**< set of keys that a player can use for movement */
        WASD,
        IJKL,
        ArrowKeys
    };

    static ControlSchemes CurrentPlayerControlSchemes[];


    /**
     * @brief Set the player number
     */
    void setPlayerNum(int pn);
    /**
     * @brief Get the player number
     */
    int getPlayerNum();
    /**
     * @brief Destructor
     */
    ~GameSetting();
    /**
     * @brief Initialization
     */
    bool init();
    /**
     * @brief Quit
     */
    bool quit();
    /**
     * @brief Update the player movement at every frame
     */
    void update();
    /**
     * @brief Load minion position from file
     */
    bool loadMinionPosition();

    // init PowerUp
    bool initPowerUps();
    // load PowerUp
    bool loadPowerUpPosition();
    /**
     * @brief Init level info
     */
    bool initMinions();

    bool initBullets();

    // // InitLevelOne
    // bool initLevelOne();
    // // InitLevelTwo
    // bool initLevelTwo();
    // // InitLevelThree
    // bool initLevelThree();
    // Win
    void win();
    // Lose
    void lose();
    /**
     * @brief Get the ball of the game
     */
    Hero* getHero();
    /**
     * @brief Get a vector of all minions of the game
     */
    vector<Minion*> getMinions();

    /**
     * @brief Get the boundary of the game
     */
    //vector<Wall*> getBoundary();

    /**
     * @brief Set level
     */
    void setLevel( int level );
    /**
     * @brief Set life
     */
    void setLife( int life );
    // set Score
    //void setScore( long int score );

    /**
     * @brief Get current level
     */
    int getLevel();
    /**
     * @brief Get the number of lives that the player has
     */
    int getLife();
    // get Score
    //long int getScore();

    /**
     * @brief Reset score to default
     */
    void resetScore();
    /**
     * @brief Reset level to default
     */
    void resetLevel();
    /**
     * @brief Reset level to default
     */
    void resetLife();
    /**
     * @brief Reset ball to original state
     */
    void resetHero();

    void reset();

    //void initWall ();

public:

    bool                    isWinConditionsSatisfied();

    void                    removeMinionByIdx(int i);

    void                    removePowerUpByIdx(int i);

    void                    addPowerUp(PowerUp* p);

    vector<PowerUp*>        getPowerUps();

    void                    addBullet(Bullet* b);

    vector<Bullet*>         getBullets();

    void                    removeBulletByIdx (int i);

    void                    removeDeadBullets();

    void                    removeDeadPowerUps();

    void                    removeDeadMinions();

private:
    /**
     * @brief Private constructor
     */
    GameSetting();

    static GameSetting* g_gameSetting; /**< the only instance */

    int playerNum = 1; /**< the player number */


    int level; /**< the Level in the game */

    // the Score in the game
    //long int score;

    int life; /**< the Life in the game */

    vector<Vector2D> minionPositions; /**< the vector of minion position */

    vector<Vector2D> powerUpPositions; // the vector of the powerUp position


private:

    Hero* hero; /**< the Hero in the game */

    vector<Minion*> minions; /**< the vector of the Minions in the game */

    vector<PowerUp*> powerUps;

    vector<Bullet*> bullets;

    //vector<Wall*> boundary; /**< the Boundary in the game */


};

#endif // GAMESETTING_H
