#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <iostream>
#include "vector2d.h"
#include "constants.h"
#include <string>
#include "canimation.h"

/**
 * @brief This class defines the game object.
 *
 * Every game object should implement GameObject class
 */
class GameObject{
public:
    /**
     * @brief Default Contructor
     */
    GameObject();
    /**
     * @brief Constructor - Only initialize position for now
     */
    GameObject(Vector2D pos);

    /**
     * @brief Destructor
     */
    ~GameObject();
    /**
     * @brief Initialization
     */
    bool init();
    /**
     * @brief Quit
     */
    void quit();

    /**
     * @brief Set the state of the game obejct
     *
     * @param s whether the object is active or not
     */
    void setState(bool s);
    /**
     * @brief Get the state of the game object
     */
    bool getState();

    /**
     * @brief Get the position of the game object
     */
    Vector2D getPosition();
    /**
     * @brief Set the position of the game object
     *
     * @param pos the position of the game object
     */
    void setPosition(Vector2D pos);

    /**
     * @brief Get the position of the game object
     */
    Vector2D getVelocity();
    /**
     * @brief Set the velocity of the game object
     *
     * @param v the velocity of the game object
     */
    void setVelocity(Vector2D v);

    /**
     * @brief Get the acceleration of the game object
     */
    Vector2D getAcceleration();
    /**
     * @brief Set the acceleration of the game object
     *
     * @param a the acceleration of the game object
     */
    void setAcceleration(Vector2D a);

    float getElastic(); /**< Get the elastic of the game obejct */

    float getMass(); /**< Get the mass of the game obejct */

    void setMass( float mass ); /**< Set the mass of the game obejct */

    /**
     * @brief Get the tag
     */
    string getTag();

    void setTag( const string& tag );

public:

    void        setPoseCode(int c);

    int         getPoseCode();

    void        setPowerCode (int c);

    int         getPowerCode();

    Vector2D    getMaxVelocity();

    void        setMaxVelocity(Vector2D v);

    void        setIsFloat (bool f);

    int         getIsFloat ();

    CAnimation*  getAnimationControl ();


protected:
    /**< the position of the game object */
    Vector2D position = Vector2D (COLLIDER_INITIAL_POSITION_X, COLLIDER_INITIAL_POSITION_Y);

    /**< the mass of the game object */
    float           mass = COLLIDER_INITIAL_MASS;

    /* the max velocity of game object on horizontal and vertical direction */
    Vector2D        maxVelocity = Vector2D(MAX_VELOCITY_X, MAX_VELOCITY_Y);

    /* the elastic of the game obejct */
    float           elastic = COLLIDER_INITIAL_ELASTIC;

    /* the velocity of the game obejct */
    Vector2D        velocity = Vector2D (COLLIDER_INITIAL_VELOCITY_X,
                                    COLLIDER_INITIAL_POSITION_Y);

    /* the acceleration of the game obejct */
    Vector2D        acceleration = Vector2D (COLLIDER_INITIAL_ACCELERATION_X, GRAVITY);

    /* the state of the game obejct */
    bool            state = IS_ALIVE;

    /* the tage of the game object */
    string          tag = "GameObject";

    /* Animation Control of Game Object*/
    CAnimation*      animationControl = new CAnimation();

    int             poseCode = 0;

    /* powerCode of Game Object*/
    int             powerCode = POWERUP_CODE_NONE;

    bool            isFloat = false;
};




/*********************            Getters and Setters             *********************/

inline string GameObject::getTag(){
    return tag;
}

// inline definitions
inline GameObject::GameObject(){

}

inline GameObject::GameObject(Vector2D pos){
    position = pos;
}

inline GameObject::~GameObject(){

}

inline bool GameObject::getState() {
    return state;
}

inline void GameObject::setState(bool s) {
    state = s;
}

inline Vector2D GameObject::getAcceleration() {
    return acceleration;
}

inline void GameObject::setAcceleration(Vector2D a) {
    acceleration = a;
}

inline Vector2D GameObject::getVelocity() {
    return velocity;
}

inline void GameObject::setVelocity(Vector2D v) {
    velocity = v;
}

inline Vector2D GameObject::getPosition() {
    return position;
}

inline void GameObject::setPosition(Vector2D p) {
    position = p;
}

inline float GameObject::getMass() {
    return mass;
}

inline float GameObject::getElastic() {
    return elastic;
}

inline void GameObject::setMass( float m ) {
    mass = m;
}

inline void GameObject::setPowerCode (int c) {
    powerCode = c;
}

inline int GameObject::getPowerCode () {
    return powerCode;
}

inline Vector2D GameObject::getMaxVelocity() {
    return maxVelocity;
}

inline void GameObject::setMaxVelocity(Vector2D v) {
    maxVelocity = v;
}

inline void GameObject::setIsFloat (bool f) {
    isFloat = f;
}

inline int GameObject::getIsFloat () {
    return isFloat;
}

inline CAnimation* GameObject::getAnimationControl () {
    return animationControl;
}

inline void GameObject::setPoseCode(int p) {
    poseCode = p;
}

inline int GameObject::getPoseCode() {
    return poseCode;
}

inline void GameObject::setTag( const string& tag ){
    this->tag = tag;
}

#endif // GAMEOBJECT_H
