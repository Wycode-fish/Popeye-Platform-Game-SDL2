#include "../include/powerup.h"


PowerUp::PowerUp(): Collider(this) {

    this->tag = "PowerUp";
    setMass( POWERUP_MASS );
    setBoundingBox( Vector2D( POWERUP_BOUNDING_BOX_X, POWERUP_BOUNDING_BOX_Y ) );
    setVelocity( Vector2D(0.0f, 0.0f) );
    setAcceleration( Vector2D(0.0f, GRAVITY) );
    this->animationControl->setMaxFrames(MINION_ANIMATION_MAX_FRAME_NUM);
    init();
}


PowerUp::PowerUp( Vector2D pos): GameObject(pos), Collider(this) {

    this->tag = "PowerUp";
    setMass( POWERUP_MASS );
    setBoundingBox( Vector2D( POWERUP_BOUNDING_BOX_X, POWERUP_BOUNDING_BOX_Y ) );
    setVelocity( Vector2D(0.0f, 0.0f) );
    setAcceleration( Vector2D(0.0f, GRAVITY) );
    this->animationControl->setMaxFrames(MINION_ANIMATION_MAX_FRAME_NUM);
    init();
}


PowerUp::~PowerUp(){}


void PowerUp::init() {
    int randomNum = rand() % POWERUP_CODE_COUNT + 1;
    setPowerCode(randomNum);
}


Vector2D PowerUp::getSize(){
    return size;
}

// setSize
void PowerUp::setSize( Vector2D s ){
    size = s;
}


