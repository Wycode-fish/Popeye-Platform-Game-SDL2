#ifndef COLLISION_H
#define COLLISION_H


#include "constants.h"
#include "collider.h"

using namespace std;

class Collision {

public:

    Collision( Collider* a, Collider* b);

    Collision( Collider* a, Collider* b, Vector2D v);

    ~Collision();

public:

    void 		init();

    void 		quit();

    Collider* 	getColliderA();

    Collider* 	getColliderB();

    int 		getColType();

    Vector2D 	getColDir();


private:

    Collider* a;

    Collider* b;

    int colType;

    Vector2D dir = Vector2D(0.0f, 0.0f);
};

#endif // COLLISION_H
