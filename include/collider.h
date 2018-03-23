#ifndef COLLIDER_H
#define COLLIDER_H

#include "vector2d.h"
#include "constants.h"
#include "gameobject.h"
#include <stdio.h>

/**
 * @brief This class is the base class for all game objects that can collide
 */
class Collider{
public:
    /**
     * @brief Default Contructor
     */
    Collider();
    /**
     * @brief Constructor
     *
     * @param the game object that can collide
     */
    Collider( GameObject* g );
    /**
     * @brief Empty destructor
     *
     * Here we can not free the gameObject pointer, because it will be
     * destrcuted by its inherited class
     */
    ~Collider();
    /**
     * @brief Determine whether this object collides with another
     *
     * @param collider the object it collides with
     */
    bool onCollide( Collider* collider );
    /**
     * @brief Callback for the collision triggered
     *
     * @param collider the object it collides with
     * @param normal the normal vector of the collider
     */
    virtual void onTriggerCollide( Collider collider, Vector2D normal );
    /**
     * @brief Set the boundary of collision detection
     */
    void setBoundingBox( Vector2D boundingBox );
    /**
     * @brief Get the boundingbox
     *
     * @return the size of the bounding box as a Vector2D
     */
    Vector2D getBoundingBox();
    /**
     * @brief Get the game object this collider represents
     *
     * @return a pointer to the game object
     */
    GameObject* getGameObject();
    /**
     * @brief Set the normal vector of this collider
     */
    void setColDir( Vector2D dir );
    /**
     * @brief Get the normal vector of this collider
     */
    Vector2D getColDir();


public:
    int         getLastColTime();

    void        setLastColTime(int t);

    bool        getIsCol();

    void        setIsCol(bool c);

//    Collider*   getOutCol();

//    void        setOutCol(Collider* o);


private:

    int         lastColTime = 0;

    bool        isCol = false;

    //Collider*   outCol;

private:
    /**
     * @brief The boundingBox of the collider
     */
    Vector2D boundingBox;
    /**
     * @brief The gameObject of the collider
     */
    GameObject* gameObject = NULL;
    /**
     * @bried The normal vector of the collider
     */
    Vector2D colDir = Vector2D(0.0f, 0.0f);
};


#endif // COLLIDER_H
