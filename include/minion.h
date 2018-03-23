#ifndef MINION_H
#define MINION_H


#include "gameobject.h"
#include "collider.h"

/**
 * @brief This class defines obstacles that a ball can collide with
 */
class Minion: public GameObject, public Collider{
public:
    /**
     * @brief Default Constructor
     */
    Minion();
    /**
     * @brief Constructor
     *
     * @para pos the position of the minion
     * @para size the size of the minion
     */
    Minion(Vector2D pos, Vector2D vel);
    /**
     * @brief Destructor
     */
    ~Minion();
    /**
     * @brief Init
     */
    bool init();
    /**
     * @brief Quit
     */
    void quit();
    // Collide, directly inherited from Collider class
    // void onCollide(Collider c);

    // *
    //  * @brief Called when the minion is collided
    //  *
    //  * @param collider the object it collides with
    //  * @param normal the normal vector of the collider

    // virtual void onTriggerCollide( Collider collider, Vector2D normal );


    /**
     * @brief Get the size (no setter for now)
     */
    Vector2D getSize();
    /**
     * @brief Set the size
     */
    void setSize( Vector2D size );

public:

    void        setPoseCode(int c);

    int         getPoseCode();


private:
    /**
     * @brief the size of the minion
     */
    Vector2D    size = Vector2D (MINION_INITIAL_WIDTH, MINION_INITIAL_HEIGHT);

    int         poseCode = MINION_POSE_STAND_RIGHT;

};

#endif // MINION_H
