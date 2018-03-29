#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include <stdio.h>
#include "vector2d.h"
#include "constants.h"
#include "gameobject.h"
#include "collider.h"
#include <typeinfo>

/**
 * @brief This class defines the bullet
 */
class Collectible : public GameObject, public Collider {
public:
    /**
     * @brief Default Constructor
     */
    Collectible();
    /**
     * @brief Constructor
     */
    Collectible( Vector2D pos, Vector2D vel );
    /**
     * @brief Destructor
     */
    ~Collectible();
    /**
     * @brief Get the radius of the bullet
     */
    Vector2D getSize();

    /**
     * @brief Set the radius of the bullet
     */
    void setSize( Vector2D s );
    // Set the velocity of the bullet
    //void setVelocity( float x, float y );
    // Set the position of the bullet
    //void setPosition( float x, float y );
    // Collide
    // void onCollide( Collider collider );
    /**
     * @brief Callback for the collision triggered
     *
     * @param collider the object it collides with
     * @param normal the normal vector of the the collider
     */
    // virtual void onTriggerCollide( Collider collider, Vector2D normal );


private:

    Vector2D size = Vector2D(BULLET_INITIAL_WIDTH, BULLET_INITIAL_HEIGHT); /**< the radius of the bullet */
};

#endif // COLLECTIBLE_H
