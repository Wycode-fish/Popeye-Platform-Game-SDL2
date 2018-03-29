#include "../include/minion.h"

// Default construtcor
Minion::Minion(): Collider( this ){
    this->tag = "Minion";
    //this->setPoseCode(MINION_POSE_STAND_RIGHT);
    this->setMass( MINION_MASS );
    this->setVelocity(Vector2D(MINION_INITIAL_VELOCITY_X, 0.0f));
    this->animationControl->setMaxFrames(MINION_ANIMATION_MAX_FRAME_NUM);
    this->setMaxVelocity(Vector2D( MINION_INITIAL_VELOCITY_X,MAX_VELOCITY_Y));
    this->setBoundingBox( Vector2D( MINION_BOUNDING_BOX_X, MINION_BOUNDING_BOX_Y ) );
}

// Constructor
Minion::Minion(Vector2D pos, Vector2D vel): Collider(this){
    this->tag = "Minion";
    //this->setPoseCode(MINION_POSE_STAND_RIGHT);
    this->setMass( MINION_MASS );
    this->setPosition(pos);
    this->setVelocity(vel);
    this->animationControl->setMaxFrames(MINION_ANIMATION_MAX_FRAME_NUM);
    this->setMaxVelocity(Vector2D( MINION_INITIAL_VELOCITY_X,MAX_VELOCITY_Y));
    this->setBoundingBox( Vector2D( MINION_BOUNDING_BOX_X, MINION_BOUNDING_BOX_Y ) );
}

// Destructor
Minion::~Minion(){

}

// getSize
Vector2D Minion::getSize(){
    return this->size;
}

// setSize
void Minion::setSize( Vector2D size ){
    this->size = size;
}

void Minion::setPoseCode(int c) {
    poseCode = c;
}


int Minion::getPoseCode() {

    return poseCode;
}
