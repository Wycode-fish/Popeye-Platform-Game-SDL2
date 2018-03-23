#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H


#include "system.h"
#include "gamesetting.h"
#include "tilemapsystem.h"
#include "controlsystem.h"
#include "collider.h"
#include "collision.h"
#include <iostream>
#include <SDL.h>

using namespace std;
/**
 * @brief This class sets up the collision system
 *
 * Singleton design pattern is applied. There is only one collision system
 * for one game.
 */
class CollisionSystem: public System{
public:
    /**
     * @brief Get the only instance of collision system
     */
    static CollisionSystem* getInstance();
    /**
     * @brief Destructor
     */
    ~CollisionSystem();
    /**
     * @brief Initialize the collision system
     */
    bool init();
    /**
     * @brief Detect collision at every frame
     *
     * This function is called every frame to detect possible collisions between
     * the ball with the paddle, the ball with four walls, and the ball with
     * bricks
     */
    void update();
    /**
     * @brief Quit the collision system
     */
    bool quit();


public:

    void removeCollisionByIdx(int i);

public:

    void colHeroMinion(Collision* c);

    void colHeroGround(Collision* c);

    void colHeroBlockUp(Collider* cHero, Vector2D* input);

    void colHeroBlockDown(Collider* cHero, Vector2D* input);

    void colHeroBlockLeft(Collider* cHero, Vector2D* input);

    void colHeroBlockRight(Collider* cHero, Vector2D* input);

    void colHeroWater(Collision* c);

    void colHeroIce(Collision* c);



    void colMinionGround(Collision* c);

    void colMinionWater(Collision* c);

    void colMinionIce(Collision* c);

    void colMinionMinion(Collision* c);


    void colHeroPowerUp(Collision* c);

    void colPowerUpGround(Collision* c);


    void colMinionBullet(Collision* c);

    void colBulletGround(Collision* c);


public:
    /****** Collision Collection ******/


    void collectCollisions();


    void collectHeroMinionCol();

    void collectHeroGroundCol();



    void collectMinionGroundCol();




    void collectHeroPowerUpCol();

    void collectPowerUpGroundCol();



    void collectMinionBulletCol();

    void collectBulletGroundCol();



private:
    /**
     * @brief Private constructor
     *
     * For a Singleton class the constructor is never used.
     */
    CollisionSystem();

    vector<Collision*> colQueue; /**< the vector of the Minions in the game */
    /**
     * @brief The only instance of collision system
     */
    static CollisionSystem* g_CollisionSystem;
};


#endif // COLLISIONSYSTEM_H
