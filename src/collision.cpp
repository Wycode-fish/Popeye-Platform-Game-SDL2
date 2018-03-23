#include "../include/collision.h"

#include <iostream>

using namespace std;

Collision::Collision( Collider* ca, Collider* cb ): a(ca), b(cb) {
    init();
}

Collision::Collision(Collider* ca, Collider* cb, Vector2D cdir): a(ca), b(cb), dir(cdir) {
    init();
}

Collision::~Collision() {
        //...
}

void Collision::init() {

    if (a!=NULL && b != NULL) {


        /*********** minion ***********/
        // hero - minion
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="Minion") ||
            (a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_MINION;

        // hero - basic (background)
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="TILE_TYPE_BASIC") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_BASIC" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_BASIC;

        // hero - surface (ground)
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="TILE_TYPE_SURFACE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SURFACE" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_SURFACE;

        // hero - water
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="TILE_TYPE_WATER") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_WATER" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_WATER;

        // hero - ice
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="TILE_TYPE_ICE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_ICE" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_ICE;



        /*********** minion ***********/
        // minion - minion
        if (a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="Minion")
            colType = COLLISION_TYPE_MINION_MINION;

        // minion - basic (background)
        if ((a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="TILE_TYPE_BASIC") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_BASIC" && b->getGameObject()->getTag()=="Minion"))
            colType = COLLISION_TYPE_MINION_BASIC;

        // minion - surface (ground)
        if ((a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="TILE_TYPE_SURFACE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SURFACE" && b->getGameObject()->getTag()=="Minion"))
            colType = COLLISION_TYPE_MINION_SURFACE;

        // minion - water
        if ((a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="TILE_TYPE_WATER") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_WATER" && b->getGameObject()->getTag()=="Minion"))
            colType = COLLISION_TYPE_MINION_WATER;

        // minion - ice
        if ((a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="TILE_TYPE_ICE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_ICE" && b->getGameObject()->getTag()=="Minion"))
            colType = COLLISION_TYPE_MINION_ICE;



        /*********** powerup ***********/
        // hero - powerup
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="PowerUp") ||
            (a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_POWERUP;

        // powerup - ground
        if ((a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="TILE_TYPE_SURFACE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SURFACE" && b->getGameObject()->getTag()=="PowerUp"))
            colType = COLLISION_TYPE_POWERUP_SURFACE;

        // powerup - ice
        if ((a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="TILE_TYPE_ICE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_ICE" && b->getGameObject()->getTag()=="PowerUp"))
            colType = COLLISION_TYPE_POWERUP_ICE;

        // powerup - water
        if ((a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="TILE_TYPE_WATER") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_WATER" && b->getGameObject()->getTag()=="PowerUp"))
            colType = COLLISION_TYPE_POWERUP_WATER;

        // powerup - basic
        if ((a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="TILE_TYPE_BASIC") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_BASIC" && b->getGameObject()->getTag()=="PowerUp"))
            colType = COLLISION_TYPE_POWERUP_BASIC;



        /*********** bullet ***********/
        // bullet - hero
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="Bullet") ||
            (a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_BULLET_HERO;

        // bullet - ground
        if ((a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="TILE_TYPE_SURFACE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SURFACE" && b->getGameObject()->getTag()=="Bullet"))
            colType = COLLISION_TYPE_BULLET_SURFACE;

        // bullet - ice
        if ((a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="TILE_TYPE_ICE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_ICE" && b->getGameObject()->getTag()=="Bullet"))
            colType = COLLISION_TYPE_BULLET_ICE;

        // bullet - water
        if ((a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="TILE_TYPE_WATER") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_WATER" && b->getGameObject()->getTag()=="Bullet"))
            colType = COLLISION_TYPE_BULLET_WATER;

        // bullet - minion
        if ((a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="Minion") ||
            (a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="Bullet"))
            colType = COLLISION_TYPE_BULLET_MINION;


    }
}

void Collision::quit() {
        //...
}

Collider* Collision::getColliderA() {
        return a;
}

Collider* Collision::getColliderB() {
        return b;
}

int Collision::getColType(){
        return colType;
}

Vector2D Collision::getColDir(){
    return dir;
}
