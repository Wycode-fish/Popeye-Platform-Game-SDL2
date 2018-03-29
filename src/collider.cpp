#include "../include/collider.h"


Collider::Collider( GameObject* gameObject ){
    this->gameObject = gameObject;
    //outCol = NULL;
    //setBoundingBox( gameObject->getSize() );
}


Collider::~Collider(){
    // Note : Here we can not free the gameObject pointer, because it will be destrcuted by its inherited class
}


bool Collider::onCollide (Collider* c) {

    string ctag = c->getGameObject()->getTag();

    if (!getGameObject()->getState() || !c->getGameObject()->getState()) return false;

    Vector2D aColliderPos = this->getGameObject()->getPosition();
    Vector2D aColliderBoundingBox = this->getBoundingBox();

    Vector2D bColliderPos = c->getGameObject()->getPosition();
    Vector2D bColliderBoundingBox = c->getBoundingBox();

//    cout << "A Collider Pos : " << aColliderPos[0] << " " << aColliderPos[1] << endl;
//    cout << "B Collider Pos : " << bColliderPos[0] << " " << bColliderPos[1] << endl;

//    cout << "A Collider B-Box : " << aColliderBoundingBox[0] << " " << aColliderBoundingBox[1] << endl;
//    cout << "B Collider B-Box : " << bColliderBoundingBox[0] << " " << bColliderBoundingBox[1] << endl;

    float aLeft = aColliderPos[0] - aColliderBoundingBox[0] / 2.0;
    float aRight = aColliderPos[0] + aColliderBoundingBox[0] / 2.0;
    float aTop = aColliderPos[1] - aColliderBoundingBox[1] / 2.0;
    float aDown = aColliderPos[1] + aColliderBoundingBox[1] / 2.0;


    float bLeft = bColliderPos[0] - bColliderBoundingBox[0] / 2.0;
    float bRight = bColliderPos[0] + bColliderBoundingBox[0] / 2.0;
    float bTop = bColliderPos[1] - bColliderBoundingBox[1] / 2.0;
    float bDown = bColliderPos[1] + bColliderBoundingBox[1] / 2.0;


    if (aDown < bTop) return false;
    if (aTop > bDown) return false;

    if (aRight < bLeft) return false;
    if (aLeft > bRight) return false;

    cout << "On Collide!\n";

    return true;
}


// onTriggerCollide
void Collider::onTriggerCollide( Collider collider, Vector2D normal ){
    std::cout << "This is the onTriggerCollider function in Collider\n";
}

// Set bounding box
void Collider::setBoundingBox( Vector2D boundingBox ){
    this->boundingBox[0] = boundingBox[0];
    this->boundingBox[1] = boundingBox[1];
}

// Get bounding box
Vector2D Collider::getBoundingBox(){
    return this->boundingBox;
}

// Set Normal Vector
void Collider::setColDir( Vector2D normal ){
    this->colDir = normal;
}

// Get Normal Vector
Vector2D Collider::getColDir(){
    return this->colDir;
}

// Get GameObject
GameObject* Collider::getGameObject(){
    return this->gameObject;
}

int Collider::getLastColTime () {
    return lastColTime;
}

void Collider::setLastColTime (int t) {
    lastColTime = t;
}

bool Collider::getIsCol () {
    return isCol;
}

void Collider::setIsCol (bool v) {
    isCol = v;
}

//Collider* Collider::getOutCol() {
//    return outCol;
//}

//void Collider::setOutCol (Collider* o) {
//    outCol = o;
//}
