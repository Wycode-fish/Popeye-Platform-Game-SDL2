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

        // hero - special
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="TILE_TYPE_SPECIAL") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SPECIAL" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_SPECIAL;




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

        // minion - special
        if ((a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="TILE_TYPE_SPECIAL") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SPECIAL" && b->getGameObject()->getTag()=="Minion"))
            colType = COLLISION_TYPE_MINION_SPECIAL;



        /*********** powerup ***********/
        // hero - powerup
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="PowerUp") ||
            (a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_POWERUP;

        // powerup - ground
        if ((a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="TILE_TYPE_SURFACE") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SURFACE" && b->getGameObject()->getTag()=="PowerUp"))
            colType = COLLISION_TYPE_POWERUP_SURFACE;

        // powerup - special
        if ((a->getGameObject()->getTag()=="PowerUp" && b->getGameObject()->getTag()=="TILE_TYPE_SPECIAL") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SPECIAL" && b->getGameObject()->getTag()=="PowerUp"))
            colType = COLLISION_TYPE_POWERUP_SPECIAL;

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
        if ((a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="TILE_TYPE_SPECIAL") ||
            (a->getGameObject()->getTag()=="TILE_TYPE_SPECIAL" && b->getGameObject()->getTag()=="Bullet"))
            colType = COLLISION_TYPE_BULLET_SPECIAL;

        // bullet - minion
        if ((a->getGameObject()->getTag()=="Bullet" && b->getGameObject()->getTag()=="Minion") ||
            (a->getGameObject()->getTag()=="Minion" && b->getGameObject()->getTag()=="Bullet"))
            colType = COLLISION_TYPE_BULLET_MINION;

        /*********** collectible ***********/
        // collectible - hero
        if ((a->getGameObject()->getTag()=="Hero" && b->getGameObject()->getTag()=="Collectible") ||
            (a->getGameObject()->getTag()=="Collectible" && b->getGameObject()->getTag()=="Hero"))
            colType = COLLISION_TYPE_HERO_COLLECTIBLE;


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
