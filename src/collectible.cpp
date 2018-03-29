#include "../include/collectible.h"

// Default Constructor
Collectible::Collectible(): Collider(this) {
    this->velocity = Vector2D( COLLECTIBLE_INITIAL_VELOCITY_X, COLLECTIBLE_INITIAL_VELOCITY_Y );
    this->tag = "Collectible";
    this->setMass( COLLECTIBLE_MASS );
    this->setBoundingBox( Vector2D( COLLECTIBLE_BOUNDING_BOX_X, COLLECTIBLE_BOUNDING_BOX_Y ) );
    this->animationControl->setMaxFrames( COLLECTIBLE_ANIMATION_MAX_FRAME_NUM );
}

// Constructor
Collectible::Collectible( Vector2D pos, Vector2D vel ): Collider(this) {
    this->tag = "Collectible";
    this->setPoseCode(HERO_POSE_STAND_RIGHT);
    this->setMass( COLLECTIBLE_MASS );
    this->setPosition(pos);
    this->setVelocity(Vector2D(0.0f,0.0f));
    this->setBoundingBox( Vector2D( COLLECTIBLE_BOUNDING_BOX_Y, COLLECTIBLE_BOUNDING_BOX_Y ) );
    this->animationControl->setMaxFrames( COLLECTIBLE_ANIMATION_MAX_FRAME_NUM );
}

// Destructor
Collectible::~Collectible(){}


// Get the radius of the ball
Vector2D Collectible::getSize(){
    return this->size;
}

// Set the radius of the ball
void Collectible::setSize( Vector2D size ){
    this->size = size;
}
