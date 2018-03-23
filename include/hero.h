#ifndef HERO_H
#define HERO_H


#include <stdio.h>
#include "gameobject.h"
#include "collider.h"
#include <typeinfo>

/**
 * @brief This class defines the hero
 */
class Hero : public GameObject, public Collider {
public:
    /**
     * @brief Default Constructor
     */
    Hero();
    /**
     * @brief Constructor
     */
    Hero( Vector2D pos, Vector2D vel );
    /**
     * @brief Destructor
     */
    ~Hero();
    /**
     * @brief Get the identifier of the hero
     */
    int getId();

    /**
     * @brief Get collide tag
     */
    bool getCollideTag();
    /**
     * @brief Set collide tag
     */
    void setCollideTag( bool colllideTag );
    // Get the position of the hero
    //Vector2D getPosition();
    // Get the speed of the hero
    //Vector2D getVelocity();
    /**
     * @brief Set the identifier of the hero
     */
    void setId( int identifier );

    // // Set the velocity of the hero
    // //void setVelocity( float x, float y );
    // // Set the position of the hero
    // //void setPosition( float x, float y );
    // // Collide
    // // void onCollide( Collider collider );
    // /**
    //  * @brief Callback for the collision triggered
    //  *
    //  * @param collider the object it collides with
    //  * @param normal the normal vector of the the collider
    //  */
    // virtual void onTriggerCollide( Collider collider, Vector2D normal );
    // /**
    //  * @brief Callback for the collision with wall
    //  *
    //  * @param collider the hero it collides with
    //  * @param normal the normal vector of the the collider
    //  */
    // void onTriggerCollideWithHero( Collider collider, Vector2D normal );
    // *
    //  * @brief Callback for the collision with boundary
    //  *
    //  * @param collider the boundary it collides with
    //  * @param normal the normal vector of the the collider

    // void onTriggerCollideWithBoundary( Collider collider, Vector2D normal );
    // /**
    //  * @brief Callback for the collision with minion
    //  *
    //  * @param collider the minion it collides with
    //  * @param normal the normal vector of the the collider
    //  */
    // void onTriggerCollideWithMinion( Collider collider, Vector2D normal );
    // /**
    //  * @brief Callback for the collision with wall
    //  *
    //  * @param collider the wall it collides with
    //  * @param normal the normal vector of the the collider
    //  */
    // void onTriggerCollideWithWall( Collider collider, Vector2D normal );
    // /**
    //  * @brief Callback for the collision with paddle
    //  *
    //  * @param collider the paddle it collides with
    //  * @param normal the normal vector of the the collider
    //  */
    // void onTriggerCollideWithPaddle( Collider collider, Vector2D normal );


public:

    void        setPoseCode(int c);

    int         getPoseCode();

private:
    int         identifier; /**< the identifier of the hero */

    Vector2D    size = Vector2D (HERO_WIDTH_INITIAL, HERO_HEIGHT_INITIAL);

    static int  currentHeroNum; /**< the current hero number */

    bool        collideTag; /**< the collision tage */

private:

    int         poseCode = HERO_POSE_STAND_RIGHT;

};

#endif // HERO_H
