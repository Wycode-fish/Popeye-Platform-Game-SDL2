#include "../include/hero.h"


int Hero::currentHeroNum = 0;


// Default Constructor
Hero::Hero(): Collider(this) {

    this->identifier = currentHeroNum++;
    this->position = Vector2D( HERO_INITIAL_POSITION_X, HERO_INITIAL_POSITION_Y );
    this->velocity = Vector2D( HERO_INITIAL_VELOCITY_X, HERO_INITIAL_VELOCITY_Y );
    this->setAcceleration( Vector2D(0, GRAVITY));
    this->tag = "Hero";
    this->animationControl->setMaxFrames( HERO_ANIMATION_MAX_FRAME_NUM );
    this->setMass( HERO_MASS );
    this->setBoundingBox( Vector2D( HERO_BOUNDING_BOX_X , HERO_BOUNDING_BOX_Y ) );



    this->collideTag = false; //???
}


// Constructor
Hero::Hero( Vector2D pos, Vector2D vel): Collider(this) {

    this->tag = "Hero";
    this->setMass( HERO_MASS );
    this->setPosition(pos);
    this->setVelocity(vel);
    this->setBoundingBox( Vector2D( HERO_BOUNDING_BOX_X , HERO_BOUNDING_BOX_Y ) );
    this->animationControl->setMaxFrames( HERO_ANIMATION_MAX_FRAME_NUM );



    this->collideTag = false;//???
}


// Destructor
Hero::~Hero(){}


// Get the identifier of the Hero
int Hero::getId(){
    return this->identifier;
}

// Set the identifier of the Hero
void Hero::setId( int identifier ){
    this->identifier = identifier;
}


// getCollideTag
bool Hero::getCollideTag(){
    return this->collideTag;
}
// setCollideTag
void Hero::setCollideTag( bool collideTag ){
    this->collideTag = collideTag;
}

void Hero::setPoseCode(int c) {
    poseCode = c;
}


int Hero::getPoseCode() {

    // if (velocity == Vector2D(0,0) && poseCode%2 == 0) {
    //     setPoseCode (HERO_POSE_STAND_LEFT);
    //     return poseCode;
    // }

    // if (velocity == Vector2D(0,0) && poseCode%2 == 1) {
    //     setPoseCode (HERO_POSE_STAND_RIGHT);
    //     return poseCode;
    // }

    // if (velocity[0]>0 && velocity[1] == 0) {
    //     setPoseCode (HERO_POSE_MOVE_RIGHT);
    //     return poseCode;
    // }

    // if (velocity[0]<0 && velocity[1] == 0) {
    //     setPoseCode (HERO_POSE_MOVE_LEFT);
    //     return poseCode;
    // }

    // if ( (poseCode%2 == 1 && velocity[1] < 0) ||
    //             (velocity[0] > 0 && velocity[1] > 0))
    // {
    //     setPoseCode (HERO_POSE_JUMP_RIGHT);
    //     return poseCode;
    // }

    // if ( (poseCode%2 == 0 && velocity[1] < 0) ||
    //             (velocity[0] < 0 && velocity[1] > 0))
    // {
    //     setPoseCode (HERO_POSE_JUMP_LEFT);
    //     return poseCode;
    // }

    // if ( (poseCode%2 == 1 && velocity[1] > 0) ||
    //             (velocity[0] > 0 && velocity[1] > 0))
    // {
    //     setPoseCode (HERO_POSE_FALL_RIGHT);
    //     return poseCode;
    // }

    // if ( (poseCode%2 == 0 && velocity[1] > 0) ||
    //             (velocity[0] < 0 && velocity[1] > 0))
    // {
    //     setPoseCode (HERO_POSE_FALL_LEFT);
    //     return poseCode;
    // }

    return poseCode;
}



