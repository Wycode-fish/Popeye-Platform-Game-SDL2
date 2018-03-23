#ifndef POWERUP_H
#define POWERUP_H


#include <stdio.h>
#include "vector2d.h"
#include "constants.h"
#include "gameobject.h"
#include "collider.h"
#include "minion.h"
#include <SDL_mixer.h>
//#include "ResourceManager.h"
//#include "ScoreSystem.h"
#include <typeinfo>

/**
 * @brief This class defines the hero
 */
class PowerUp : public GameObject, public Collider {
public:
    /**
     * @brief Default Constructor
     */
    PowerUp();
    /**
     * @brief Constructor
     */
    PowerUp( Vector2D pos );
    /**
     * @brief Destructor
     */
    ~PowerUp();

    /**
     * @brief Get the size (no setter for now)
     */
    Vector2D getSize();
    /**
     * @brief Set the size
     */
    void setSize( Vector2D size );
    /**
     * @brief Callback for the collision triggered
     *
     * @param collider the object it collides with
     * @param normal the normal vector of the the collider
     */

    void init();



private:

    Vector2D size = Vector2D (POWERUP_INITIAL_WIDTH, POWERUP_INITIAL_HEIGHT);

};

#endif // POWERUP_H
