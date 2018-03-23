#include "../include/bullet.h"


// Default Constructor
Bullet::Bullet(): Collider(this) {
    this->velocity = Vector2D( BULLET_INITIAL_VELOCITY_X, BULLET_INITIAL_VELOCITY_Y );
    this->tag = "Bullet";
    this->setMass( BULLET_MASS );
    this->setBoundingBox( Vector2D( BULLET_BOUNDING_BOX_X, BULLET_BOUNDING_BOX_Y ) );
    this->animationControl->setMaxFrames( BULLET_ANIMATION_MAX_FRAME_NUM );
}

// Constructor
Bullet::Bullet( Vector2D pos, Vector2D vel ): Collider(this) {
    this->tag = "Bullet";
    this->setPoseCode(HERO_POSE_STAND_RIGHT);
    this->setMass( BULLET_MASS );
    this->setPosition(pos);
    this->setVelocity(vel);
    this->setBoundingBox( Vector2D( BULLET_BOUNDING_BOX_Y, BULLET_BOUNDING_BOX_Y ) );
    this->animationControl->setMaxFrames( BULLET_ANIMATION_MAX_FRAME_NUM );
}

// Destructor
Bullet::~Bullet(){}


// Get the radius of the ball
Vector2D Bullet::getSize(){
    return this->size;
}

// Set the radius of the ball
void Bullet::setSize( Vector2D size ){
    this->size = size;
}



