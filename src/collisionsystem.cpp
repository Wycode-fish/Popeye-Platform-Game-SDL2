#include "../include/collisionsystem.h"



CollisionSystem* CollisionSystem::g_CollisionSystem = NULL;

// getInstance function
CollisionSystem* CollisionSystem::getInstance(){
    if (!g_CollisionSystem)
        g_CollisionSystem = new CollisionSystem();
    return g_CollisionSystem;
}

// Default constructor
CollisionSystem::CollisionSystem(){}

// Default destructor
CollisionSystem::~CollisionSystem(){}

// init
bool CollisionSystem::init(){
    bool success = true;
    std::cout << "Initialize CollisionSystem!\n";
    return success;
}

void CollisionSystem::collectCollisions() {

    cout<<"***** collecting *****"<<endl;

    collectHeroMinionCol();

    collectHeroGroundCol();



    collectMinionGroundCol();



    collectHeroPowerUpCol();

    collectPowerUpGroundCol();



    collectMinionBulletCol();

    collectBulletGroundCol();

    collectHeroCollectibleCol();

}


// update
void CollisionSystem::update(){

    collectCollisions();

    // Deal with Collisions in Queue.
    for (int i=0; i<colQueue.size(); i++) {

        int colType = colQueue[i]->getColType();

        switch (colType) {

            case COLLISION_TYPE_HERO_MINION :       // COLLISION_TYPE_HERO_MINION          1
                cout<<"--------- minion collide."<<endl;
                colHeroMinion( colQueue[i] );
                break;

            /****** Hero Collision ******/

            case COLLISION_TYPE_HERO_BASIC :       // COLLISION_TYPE_HERO_GROUND          2
                break;

            case COLLISION_TYPE_HERO_SPECIAL :       // COLLISION_TYPE_HERO_GROUND          2
                colHeroSpecial( colQueue[i] );
                break;

            case COLLISION_TYPE_HERO_SURFACE :       // COLLISION_TYPE_HERO_GROUND          2
                cout<<"--------- surface."<<endl;
                colHeroGround( colQueue[i] );
                break;

            /****** Minion Collision ******/
            case COLLISION_TYPE_MINION_BASIC :
                break;

            case COLLISION_TYPE_MINION_SURFACE :
                cout<<"--------- minion surface."<<endl;
                colMinionGround( colQueue[i] );
                break;

            case COLLISION_TYPE_MINION_SPECIAL :
                colMinionSpecial( colQueue[i] );
                break;

            case COLLISION_TYPE_MINION_MINION :
                colMinionMinion( colQueue[i] );
                break;


            /****** PowerUp Collision ******/
            case COLLISION_TYPE_HERO_POWERUP :
                colHeroPowerUp( colQueue[i] );
                break;

            case COLLISION_TYPE_POWERUP_SURFACE :
                colPowerUpGround( colQueue[i] );
                break;

            case COLLISION_TYPE_POWERUP_SPECIAL :
                colPowerUpSpecial( colQueue[i] );
                break;

            case COLLISION_TYPE_POWERUP_BASIC :
                break;


            /****** Bullet Collision ******/
            case COLLISION_TYPE_BULLET_MINION :
                colMinionBullet ( colQueue[i] );
                break;

            case COLLISION_TYPE_BULLET_SPECIAL :
                colBulletSpecial ( colQueue[i] );
                break;

            case COLLISION_TYPE_BULLET_SURFACE :
                colBulletGround ( colQueue[i] );
                break;

            case COLLISION_TYPE_BULLET_HERO :
                colBulletHero ( colQueue[i] );
                break;

            /****** Collectible Collision ******/
            case COLLISION_TYPE_HERO_COLLECTIBLE :
                colHeroCollectible ( colQueue[i] );
                break;


            default:
                cout<<"None of Predefined Collision Satisfies this Collision!"<<endl;
        }
    }

    colQueue.erase(colQueue.begin(), colQueue.end());
    colQueue.clear();
}


/*************************.    Collision Update Helper Function  *************************/
void CollisionSystem::colHeroCollectible(Collision* c) {


    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();


    Collider* cHero = (a->getGameObject()->getTag() == "Hero") ? a : b;
    Collider* cCollectible = (a->getGameObject()->getTag() == "Collectible") ? a : b;

    // Collision Effect
    // cHero->getGameObject()->setLastPowerTime(SDL_GetTicks());
    // cHero->getGameObject()->setPowerCode(cPowerUp->getGameObject()->getPowerCode());

    if (!cCollectible->getIsCol()) {          // If powerup is collision valid
        cCollectible->setIsCol(true);
        cCollectible->setLastColTime(SDL_GetTicks());
    }
}

void CollisionSystem::colHeroMinion(Collision* c) {

    cout<<"collision: hero <-> minion"<<endl;

    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cHero = (a->getGameObject()->getTag()=="Hero")?a:b;
    Collider* cMinion = (a->getGameObject()->getTag()=="Minion")?a:b;

    // Collision Effect
    if (!cHero->getIsCol()) {          // If hero is collision valid
        cHero->setIsCol(true);
        GameSetting::getInstance()->setLife( GameSetting::getInstance()->getLife() - 1 );
        cout << "Life Left : " << GameSetting::getInstance()->getLife() << endl;
        cHero->setLastColTime(SDL_GetTicks());
    }

    if (!cMinion->getIsCol()) {        // if minion is collision valid
        cMinion->setIsCol(true);
        cMinion->setLastColTime(SDL_GetTicks());
    }
}


void CollisionSystem::colHeroGround(Collision* c) {

    cout<<"collision: hero <-> surface"<<endl;

    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cHero = (a->getGameObject()->getTag()=="Hero")?a:b;
    Collider* cTile = (a->getGameObject()->getTag()=="Hero")?b:a;

    Vector2D* input = ControlSystem::getInstance()->translateInput(GameSetting::getInstance()->getPlayerNum()-1);

    if (c->getColDir()==Vector2D(0.0f, 1.0f)){

        colHeroBlockDown(cHero, input);
    }

    if (c->getColDir()==Vector2D(0.0f, -1.0f)){

        colHeroBlockUp(cHero, input);
    }
    if (c->getColDir()==Vector2D(1.0f, 0.0f)){

        colHeroBlockRight(cHero, input);
    }

    if (c->getColDir()==Vector2D(-1.0f, 0.0f)){

        colHeroBlockLeft(cHero, input);
    }


}

void CollisionSystem::colHeroSpecial(Collision* c){
    cout<<"collision: hero <-> special"<<endl;

    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cHero = (a->getGameObject()->getTag()=="Hero")?a:b;
    Collider* cTile = (a->getGameObject()->getTag()=="Hero")?b:a;

    Vector2D* input = ControlSystem::getInstance()->translateInput(GameSetting::getInstance()->getPlayerNum()-1);

    if (c->getColDir()==Vector2D(0.0f, 1.0f)){

        colHeroSpecialBlockDown(cHero, input);
    }

    if (c->getColDir()==Vector2D(0.0f, -1.0f)){

        colHeroSpecialBlockUp(cHero, input);
    }

    if (c->getColDir()==Vector2D(1.0f, 0.0f)){

        colHeroSpecialBlockRight(cHero, input);
    }

    if (c->getColDir()==Vector2D(-1.0f, 0.0f)){

        colHeroSpecialBlockLeft(cHero, input);
    }


}

//void CollisionSystem::colHeroWater(Collision* c) {
//    return;
//}

//void CollisionSystem::colHeroIce(Collision* c) {
//    return;
//}



void CollisionSystem::colMinionGround(Collision* c) {

    cout<<"collision: minion <-> surface"<<endl;


    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cMinion = (a->getGameObject()->getTag()=="Minion")?a:b;
    Collider* cTile = (a->getGameObject()->getTag()=="Minion")?b:a;

    if (c->getColDir()==Vector2D(0.0f, 1.0f)){

//        cMinion->getGameObject()->setAcceleration( Vector2D( cMinion->getGameObject()->getAcceleration()[0], 0));
//        cMinion->getGameObject()->setVelocity( Vector2D( cMinion->getGameObject()->getVelocity()[0], 0));
        colMinionBlockDown(cMinion);
    }

    if (c->getColDir()==Vector2D(0.0f, -1.0f)){
//        cMinion->getGameObject()->setAcceleration( Vector2D( cMinion->getGameObject()->getAcceleration()[0], GRAVITY));
//        cMinion->getGameObject()->setVelocity( Vector2D( cMinion->getGameObject()->getVelocity()[0], 0));
        colMinionBlockUp(cMinion);
    }

    if (c->getColDir()==Vector2D(1.0f, 0.0f)){

/*        cMinion->getGameObject()->setAcceleration( Vector2D( 0.0f, cMinion->getGameObject()->getAcceleration()[1]));
        cMinion->getGameObject()->setVelocity( Vector2D( (-1.0f)*cMinion->getGameObject()->getVelocity()[0], cMinion->getGameObject()->getVelocity()[1]));*/
        colMinionBlockRight(cMinion);
    }

    if (c->getColDir()==Vector2D(-1.0f, 0.0f)){
        colMinionBlockLeft(cMinion);
    }

}


void CollisionSystem::colMinionBlockUp(Collider* c){

    if (c->getGameObject()->getVelocity()[1] <= (-1)*c->getGameObject()->getMaxVelocity()[1]) {

        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], 0.0f));

    }
    else if (c->getGameObject()->getVelocity()[1] >= 0){

        c->getGameObject()->setAcceleration( Vector2D( c->getGameObject()->getAcceleration()[0], GRAVITY));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));
    }
}

void CollisionSystem::colMinionBlockDown(Collider* c){

        c->getGameObject()->setAcceleration( Vector2D( c->getGameObject()->getAcceleration()[0], 0));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], 0.0f));

}

void CollisionSystem::colMinionBlockLeft(Collider* c){


    if (c->getGameObject()->getVelocity()[0] <= (-1)*c->getGameObject()->getMaxVelocity()[0]) {

        c->getGameObject()->setVelocity( Vector2D((-1) * c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));

    }
    else if (c->getGameObject()->getVelocity()[0] >= 0){

        c->getGameObject()->setAcceleration( Vector2D( 0.0f, c->getGameObject()->getAcceleration()[1]));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));
    }

}

void CollisionSystem::colMinionBlockRight(Collider* c){

    if (c->getGameObject()->getVelocity()[0] >= c->getGameObject()->getMaxVelocity()[0]) {

        c->getGameObject()->setVelocity( Vector2D( (-1) * c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));

    }
    else if (c->getGameObject()->getVelocity()[0] <= 0){

        c->getGameObject()->setAcceleration( Vector2D( 0.0f, c->getGameObject()->getAcceleration()[1]));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));
    }
}

void CollisionSystem::colMinionSpecialBlockUp(Collider* c){

    if (c->getGameObject()->getVelocity()[1] <= (-1)*c->getGameObject()->getMaxVelocity()[1]) {

        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], 0.0f));

    }
    else if (c->getGameObject()->getVelocity()[1] >= 0){

        c->getGameObject()->setAcceleration( Vector2D( c->getGameObject()->getAcceleration()[0], GRAVITY));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));
    }
}

void CollisionSystem::colMinionSpecialBlockDown(Collider* c){

        c->getGameObject()->setAcceleration( Vector2D( c->getGameObject()->getAcceleration()[0], 0));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], 0.0f));

}

void CollisionSystem::colMinionSpecialBlockLeft(Collider* c){


    if (c->getGameObject()->getVelocity()[0] <= (-1)*c->getGameObject()->getMaxVelocity()[0]) {

        c->getGameObject()->setVelocity( Vector2D((-1) * c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));

    }
    else if (c->getGameObject()->getVelocity()[0] >= 0){

        c->getGameObject()->setAcceleration( Vector2D( 0.0f, c->getGameObject()->getAcceleration()[1]));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));
    }

}

void CollisionSystem::colMinionSpecialBlockRight(Collider* c){

    if (c->getGameObject()->getVelocity()[0] >= c->getGameObject()->getMaxVelocity()[0]) {

        c->getGameObject()->setVelocity( Vector2D((-1) * c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));

    }
    else if (c->getGameObject()->getVelocity()[0] <= 0){

        c->getGameObject()->setAcceleration( Vector2D( 0.0f, c->getGameObject()->getAcceleration()[1]));
        c->getGameObject()->setVelocity( Vector2D( c->getGameObject()->getVelocity()[0], c->getGameObject()->getVelocity()[1]));
    }
}

void CollisionSystem::colMinionMinion(Collision* c) {
    return;
}

void CollisionSystem::colMinionSpecial(Collision* c) {

    cout<<"collision: minion <-> special"<<endl;


    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cMinion = (a->getGameObject()->getTag()=="Minion")?a:b;
    Collider* cTile = (a->getGameObject()->getTag()=="Minion")?b:a;

    if (c->getColDir()==Vector2D(0.0f, 1.0f)){

//        cMinion->getGameObject()->setAcceleration( Vector2D( cMinion->getGameObject()->getAcceleration()[0], 0));
//        cMinion->getGameObject()->setVelocity( Vector2D( cMinion->getGameObject()->getVelocity()[0], 0));
        colMinionSpecialBlockDown(cMinion);
    }

    if (c->getColDir()==Vector2D(0.0f, -1.0f)){
//        cMinion->getGameObject()->setAcceleration( Vector2D( cMinion->getGameObject()->getAcceleration()[0], GRAVITY));
//        cMinion->getGameObject()->setVelocity( Vector2D( cMinion->getGameObject()->getVelocity()[0], 0));
        colMinionSpecialBlockUp(cMinion);
    }

    if (c->getColDir()==Vector2D(1.0f, 0.0f)){

/*        cMinion->getGameObject()->setAcceleration( Vector2D( 0.0f, cMinion->getGameObject()->getAcceleration()[1]));
        cMinion->getGameObject()->setVelocity( Vector2D( (-1.0f)*cMinion->getGameObject()->getVelocity()[0], cMinion->getGameObject()->getVelocity()[1]));*/
        colMinionSpecialBlockRight(cMinion);
    }

    if (c->getColDir()==Vector2D(-1.0f, 0.0f)){
        colMinionSpecialBlockLeft(cMinion);
    }
}



void CollisionSystem::colMinionBullet(Collision* c) {

    cout<<"collision: minion <-> bullet"<<endl;

    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cMinion = (a->getGameObject()->getTag()=="Minion")?a:b;
    Collider* cBullet = (a->getGameObject()->getTag()=="Bullet")?a:b;

    cMinion->getGameObject()->setState(IS_DEAD);
    cBullet->getGameObject()->setState(IS_DEAD);
}



void CollisionSystem::colHeroPowerUp(Collision* c) {


    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();


    Collider* cHero = (a->getGameObject()->getTag() == "Hero") ? a : b;
    Collider* cPowerUp = (a->getGameObject()->getTag() == "PowerUp") ? a : b;

    // Collision Effect
    cHero->getGameObject()->setLastPowerTime(SDL_GetTicks());
    cHero->getGameObject()->setPowerCode(cPowerUp->getGameObject()->getPowerCode());


    if (!cPowerUp->getIsCol()) {          // If powerup is collision valid
        cPowerUp->setIsCol(true);
        cPowerUp->setLastColTime(SDL_GetTicks());
//        SoundSystem::getInstance()->playPowerUpSound();
    }
}


void CollisionSystem::colPowerUpGround(Collision* c) {

    cout<<"collision: powerUp <-> Ground"<<endl;

    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

//    if ((a->getGameObject() == NULL) || (b->getGameObject() == NULL))
//        cout << "Can not get the GameObject !\n";

//    cout << "PowerUp Collide with Ground Tag : " << a->getGameObject()->getTag() << endl;

    Collider* cPowerUp = (a->getGameObject()->getTag()=="PowerUp")?a:b;

//    if (cPowerUp->getGameObject() == NULL){
//        cout << "PowerUp has no GameObject!\n";
//    }

    cPowerUp->getGameObject()->setAcceleration( Vector2D( cPowerUp->getGameObject()->getAcceleration()[0], 0));
    cPowerUp->getGameObject()->setVelocity( Vector2D( cPowerUp->getGameObject()->getVelocity()[0], 0));
}

void CollisionSystem::colPowerUpSpecial(Collision* c){
    return;
}

void CollisionSystem::colBulletGround(Collision* c) {

    cout<<"collision: surface <-> bullet"<<endl;

    Collider* a = c->getColliderA();
    Collider* b = c->getColliderB();

    Collider* cBullet = (a->getGameObject()->getTag()=="Bullet")?a:b;

    cBullet->getGameObject()->setState(IS_DEAD);
}

void CollisionSystem::colBulletSpecial(Collision *c){
    return;
}

void CollisionSystem::colBulletHero(Collision* c){
    return;
}


/*************************.    Collision Collection Helper Function  *************************/
// All this position is relative the map coordinate system, the origin is in the left-top corner

void CollisionSystem::collectHeroCollectibleCol() {

    Hero* hero = GameSetting::getInstance()->getHero();

    vector<Collectible*> collectibles = GameSetting::getInstance()->getCollectibles();

    for (int i=0; i<collectibles.size(); i++) {

        if ( hero->onCollide(collectibles[i])){
            this->colQueue.push_back(new Collision(hero, collectibles[i]));
        }
    }
}

void CollisionSystem::collectHeroMinionCol() {

    Hero* hero = GameSetting::getInstance()->getHero();

    vector<Minion*> minions = GameSetting::getInstance()->getMinions();

    for (int i=0; i<minions.size(); i++) {
        if ( hero->onCollide(minions[i])){
            cout << "Detect that Hero collides with Minion[" << i << "] !\n";
            this->colQueue.push_back(new Collision(hero, minions[i]));
        }
    }
}

void CollisionSystem::collectHeroGroundCol() {

    Hero* hero = GameSetting::getInstance()->getHero();

    TileMap* currTileMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );

    Tile* CLTile = currTileMap->tileAtLeftPos(hero->getPosition());

    Tile* CRTile = currTileMap->tileAtRightPos(hero->getPosition());

    Tile* CUTile = currTileMap->tileAtUpPos(hero->getPosition());

    Tile* CDTile = currTileMap->tileAtDownPos(hero->getPosition());

    if (CUTile != NULL){
        if (hero->onCollide(CUTile))
            this->colQueue.push_back(new Collision(hero, CUTile, Vector2D(0.0, -1.0)));
    }

    if (CDTile != NULL){
        if (hero->onCollide(CDTile))
            this->colQueue.push_back(new Collision(hero, CDTile, Vector2D(0.0, 1.0)));
    }

    if (CLTile != NULL){
        if (hero->onCollide(CLTile))
            this->colQueue.push_back(new Collision(hero, CLTile, Vector2D(-1.0, 0.0)));
    }


    if (CRTile != NULL){
        if (hero->onCollide(CRTile))
            this->colQueue.push_back(new Collision(hero, CRTile, Vector2D(1.0, 0.0)));
    }




}

void CollisionSystem::collectMinionGroundCol() {

    vector<Minion*> minions = GameSetting::getInstance()->getMinions();

    TileMap* currTileMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );

    for (int i=0; i<minions.size(); i++) {

        Tile* CLTile = currTileMap->tileAtLeftPos(minions[i]->getPosition());

        Tile* CRTile = currTileMap->tileAtRightPos(minions[i]->getPosition());

        Tile* CUTile = currTileMap->tileAtUpPos(minions[i]->getPosition());

        Tile* CDTile = currTileMap->tileAtDownPos(minions[i]->getPosition());

        if (CLTile != NULL){
            if (minions[i]->onCollide(CLTile))
                this->colQueue.push_back(new Collision(minions[i], CLTile, Vector2D(-1.0, 0.0)));
        }

        if (CRTile != NULL){
            if (minions[i]->onCollide(CRTile))
                this->colQueue.push_back(new Collision(minions[i], CRTile, Vector2D(1.0, 0.0)));
        }

        if (CUTile != NULL){
            if (minions[i]->onCollide(CUTile))
                this->colQueue.push_back(new Collision(minions[i], CUTile, Vector2D(0.0, -1.0)));
        }

        if (CDTile != NULL){
            if (minions[i]->onCollide(CDTile))
                this->colQueue.push_back(new Collision(minions[i], CDTile, Vector2D(0.0, 1.0)));
        }

    }
}

void CollisionSystem::collectMinionBulletCol() {

    vector<Minion*> minions = GameSetting::getInstance()->getMinions();
    vector<Bullet*> bullets = GameSetting::getInstance()->getBullets();

    for (int i=0; i<minions.size(); i++) {

        for (int j=0; j<bullets.size(); j++) {

            if (minions[i]->onCollide(bullets[j])){
                SoundSystem::getInstance()->playKickSound();
                this->colQueue.push_back(new Collision(minions[i], bullets[j]));
            }
        }
    }
}

void CollisionSystem::collectBulletGroundCol() {


    vector<Bullet*> bullets = GameSetting::getInstance()->getBullets();

    TileMap* currTileMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );

    for (int i=0; i<bullets.size(); i++) {

        Tile* CLTile = currTileMap->tileAtLeftPos(bullets[i]->getPosition());

        Tile* CRTile = currTileMap->tileAtRightPos(bullets[i]->getPosition());

        Tile* CUTile = currTileMap->tileAtUpPos(bullets[i]->getPosition());

        Tile* CDTile = currTileMap->tileAtDownPos(bullets[i]->getPosition());

        if (CLTile != NULL){
            if (bullets[i]->onCollide(CLTile))
                this->colQueue.push_back(new Collision(bullets[i], CLTile, Vector2D(-1.0, 0.0)));
        }

        if (CRTile != NULL){
            if (bullets[i]->onCollide(CRTile))
                this->colQueue.push_back(new Collision(bullets[i], CRTile, Vector2D(1.0, 0.0)));
        }

        if (CUTile != NULL){
            if (bullets[i]->onCollide(CUTile))
                this->colQueue.push_back(new Collision(bullets[i], CUTile, Vector2D(0.0, -1.0)));
        }

        if (CDTile != NULL){
            if (bullets[i]->onCollide(CDTile))
                this->colQueue.push_back(new Collision(bullets[i], CDTile, Vector2D(0.0, 1.0)));
        }

    }
}

void CollisionSystem::collectHeroPowerUpCol() {

    Hero* hero = GameSetting::getInstance()->getHero();

    vector<PowerUp*> powerUps = GameSetting::getInstance()->getPowerUps();

    for (int i=0; i<powerUps.size(); i++) {

        if ( hero->onCollide(powerUps[i])){
//            SoundSystem::getInstance()->playPowerUpSound();
            cout << "Detect that hero collides with powerUp[" << i << "] !\n";
            this->colQueue.push_back(new Collision(hero, powerUps[i]));
        }
    }
}

void CollisionSystem::collectPowerUpGroundCol() {

    vector<PowerUp*> powerUps = GameSetting::getInstance()->getPowerUps();

    TileMap* currTileMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );

    for (int i=0; i<powerUps.size(); i++) {

        Tile* CLTile = currTileMap->tileAtLeftPos(powerUps[i]->getPosition());

        Tile* CRTile = currTileMap->tileAtRightPos(powerUps[i]->getPosition());

        Tile* CUTile = currTileMap->tileAtUpPos(powerUps[i]->getPosition());

        Tile* CDTile = currTileMap->tileAtDownPos(powerUps[i]->getPosition());

        if (CLTile != NULL){
            if (powerUps[i]->onCollide(CLTile))
                this->colQueue.push_back(new Collision(powerUps[i], CLTile, Vector2D(-1.0, 0.0)));
        }

        if (CRTile != NULL){
            if (powerUps[i]->onCollide(CRTile))
                this->colQueue.push_back(new Collision(powerUps[i], CRTile, Vector2D(1.0, 0.0)));
        }

        if (CUTile != NULL){
            if (powerUps[i]->onCollide(CUTile))
                this->colQueue.push_back(new Collision(powerUps[i], CUTile, Vector2D(0.0, -1.0)));
        }

        if (CDTile != NULL){
            if (powerUps[i]->onCollide(CDTile))
                this->colQueue.push_back(new Collision(powerUps[i], CDTile, Vector2D(0.0, 1.0)));
        }

    }
}

void CollisionSystem::colHeroBlockRight(Collider* cHero, Vector2D* input) {

    if ((*input)[0]>0){
        Vector2D* nv = new Vector2D(0.0f, (*input)[1]);
        ControlSystem::getInstance()->reset();
    }

    if (cHero->getGameObject()->getVelocity()[0] >= cHero->getGameObject()->getMaxVelocity()[0]) {

        cHero->getGameObject()->setVelocity( Vector2D(0.0f, cHero->getGameObject()->getVelocity()[1]));

    }
    else if (cHero->getGameObject()->getVelocity()[0] <= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( 0.0f, cHero->getGameObject()->getAcceleration()[1]));
        cHero->getGameObject()->setVelocity( Vector2D( 0.0f, cHero->getGameObject()->getVelocity()[1]));
    }

    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );

}


void CollisionSystem::colHeroBlockLeft(Collider* cHero, Vector2D* input) {

    if ((*input)[0]<0){
        Vector2D* nv = new Vector2D(0.0f, (*input)[1]);
        ControlSystem::getInstance()->reset();
    }


    if (cHero->getGameObject()->getVelocity()[0] <= (-1)*cHero->getGameObject()->getMaxVelocity()[0]) {

        cHero->getGameObject()->setVelocity( Vector2D(0.0f, cHero->getGameObject()->getVelocity()[1]));

    }
    else if (cHero->getGameObject()->getVelocity()[0] <= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( 0.0f, cHero->getGameObject()->getAcceleration()[1]));
        cHero->getGameObject()->setVelocity( Vector2D( 0.0f, cHero->getGameObject()->getVelocity()[1]));
    }
    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );

}

void CollisionSystem::colHeroBlockDown(Collider* cHero, Vector2D* input) {

    //cout<<"^^^^^^^^^^ velocity: "+to_string(cHero->getGameObject()->getVelocity()[0])+", "+to_string(cHero->getGameObject()->getVelocity()[1])<<endl;

    cHero->getGameObject()->setIsFloat(false);

    if ((*input)[1]>0){
        Vector2D* nv = new Vector2D((*input)[0], 0.0f);
        ControlSystem::getInstance()->reset();
    }

    if (cHero->getGameObject()->getVelocity()[1] >= cHero->getGameObject()->getMaxVelocity()[1]) {

        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], 0.0f));

    }
    else if (cHero->getGameObject()->getVelocity()[1] >= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( cHero->getGameObject()->getAcceleration()[0], 0));
        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], 0.0f));
    }

    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );


}


void CollisionSystem::colHeroBlockUp(Collider* cHero, Vector2D* input) {

    //cout<<"$$$$$$$$$$$ velocity: "+to_string(cHero->getGameObject()->getVelocity()[0])+", "+to_string(cHero->getGameObject()->getVelocity()[1])<<endl;
    if ((*input)[1]<0){
            Vector2D* nv = new Vector2D((*input)[0], 0.0f);
            ControlSystem::getInstance()->reset();
    }

    if (cHero->getGameObject()->getVelocity()[1] <= (-1)*cHero->getGameObject()->getMaxVelocity()[1]) {

        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], 0.0f));

    }
    else if (cHero->getGameObject()->getVelocity()[1] <= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( cHero->getGameObject()->getAcceleration()[0], GRAVITY));
        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], (-1)*cHero->getGameObject()->getVelocity()[1]));
    }
    // cHero->getGameObject()->setAcceleration( Vector2D( cHero->getGameObject()->getAcceleration()[0], GRAVITY));
    // cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], cHero->getGameObject()->getMaxVelocity()[1]));

    // Vector2D npos = cHero->getGameObject()->getPosition()+;

    // cHero->getGameObject()->setPosition( npos );
    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );


}

void CollisionSystem::colHeroSpecialBlockRight(Collider* cHero, Vector2D* input) {

    if ((*input)[0]>0){
        Vector2D* nv = new Vector2D(0.0f, (*input)[1]);
        ControlSystem::getInstance()->reset();
    }
    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );
    Vector2D specialAccEffect = currentMap->getSpecialAccEffect();
    Vector2D inputFactorEffect = currentMap->getInputFactorEffect();
    int specialLifeEffect = currentMap->getSpecialLifeEffect();
    int currentLife = GameSetting::getInstance()->getLife() - specialLifeEffect;
    GameSetting::getInstance()->setLife( currentLife );

    if (cHero->getGameObject()->getVelocity()[0] >= cHero->getGameObject()->getMaxVelocity()[0]) {

        cHero->getGameObject()->setVelocity( Vector2D(0.0f, cHero->getGameObject()->getVelocity()[1]));

    }
    else if (cHero->getGameObject()->getVelocity()[0] >= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( 0.0f, cHero->getGameObject()->getAcceleration()[1]));
        cHero->getGameObject()->setVelocity( Vector2D( 0.0f, cHero->getGameObject()->getVelocity()[1]));
    }
    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );

}

void CollisionSystem::colHeroSpecialBlockLeft(Collider *cHero, Vector2D *input) {

    if ((*input)[0]<0){
        Vector2D* nv = new Vector2D(0.0f, (*input)[1]);
        ControlSystem::getInstance()->reset();
    }

    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );
    Vector2D specialAccEffect = currentMap->getSpecialAccEffect();
    Vector2D inputFactorEffect = currentMap->getInputFactorEffect();
    int specialLifeEffect = currentMap->getSpecialLifeEffect();
    int currentLife = GameSetting::getInstance()->getLife() - specialLifeEffect;
    GameSetting::getInstance()->setLife( currentLife );

    if (cHero->getGameObject()->getVelocity()[0] <= (-1)*cHero->getGameObject()->getMaxVelocity()[0]) {

        cHero->getGameObject()->setVelocity( Vector2D(0.0f, cHero->getGameObject()->getVelocity()[1]));

    }
    else if (cHero->getGameObject()->getVelocity()[0] <= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( 0.0f, cHero->getGameObject()->getAcceleration()[1]));
        cHero->getGameObject()->setVelocity( Vector2D( 0.0f, cHero->getGameObject()->getVelocity()[1]));
    }

    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );

}

void CollisionSystem::colHeroSpecialBlockDown(Collider* cHero, Vector2D* input) {

    //cout<<"^^^^^^^^^^ velocity: "+to_string(cHero->getGameObject()->getVelocity()[0])+", "+to_string(cHero->getGameObject()->getVelocity()[1])<<endl;

    cHero->getGameObject()->setIsFloat(false);

    if ((*input)[1]>0){
        Vector2D* nv = new Vector2D((*input)[0], 0.0f);
        ControlSystem::getInstance()->reset();
    }

    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );

    Vector2D specialAccEffect = currentMap->getSpecialAccEffect();
    Vector2D inputFactorEffect = currentMap->getInputFactorEffect();
    int specialLifeEffect = currentMap->getSpecialLifeEffect();

    int currentLife = GameSetting::getInstance()->getLife() - specialLifeEffect;

    GameSetting::getInstance()->setLife( currentLife );



    if (cHero->getGameObject()->getVelocity()[1] >= cHero->getGameObject()->getMaxVelocity()[1]) {

        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], 0.0f));

    }
    else if (cHero->getGameObject()->getVelocity()[1] >= 0){

        specialAccEffect[0] = (cHero->getGameObject()->getAcceleration()[0] >= 0)? specialAccEffect[0] : (-specialAccEffect[0]);

        specialAccEffect[1] = (cHero->getGameObject()->getAcceleration()[1] >= 0)? specialAccEffect[1] : (-specialAccEffect[0]);

        cHero->getGameObject()->setAcceleration( Vector2D( cHero->getGameObject()->getAcceleration()[0] + specialAccEffect[0]
                                                 , 0.0f + specialAccEffect[1]));
        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], 0.0f));

        ControlSystem::getInstance()->setInputFactors( inputFactorEffect );
    }

}

void CollisionSystem::colHeroSpecialBlockUp(Collider* cHero, Vector2D* input) {

    //cout<<"$$$$$$$$$$$ velocity: "+to_string(cHero->getGameObject()->getVelocity()[0])+", "+to_string(cHero->getGameObject()->getVelocity()[1])<<endl;
    if ((*input)[1]<0){
            Vector2D* nv = new Vector2D((*input)[0], 0.0f);
            ControlSystem::getInstance()->reset();
    }

    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );
    Vector2D specialAccEffect = currentMap->getSpecialAccEffect();
    Vector2D inputFactorEffect = currentMap->getInputFactorEffect();
    int specialLifeEffect = currentMap->getSpecialLifeEffect();
    int currentLife = GameSetting::getInstance()->getLife() - specialLifeEffect;
    GameSetting::getInstance()->setLife( currentLife );

    if (cHero->getGameObject()->getVelocity()[1] <= (-1)*cHero->getGameObject()->getMaxVelocity()[1]) {

        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], 0.0f));

    }
    else if (cHero->getGameObject()->getVelocity()[1] <= 0){

        cHero->getGameObject()->setAcceleration( Vector2D( cHero->getGameObject()->getAcceleration()[0], GRAVITY));
        cHero->getGameObject()->setVelocity( Vector2D( cHero->getGameObject()->getVelocity()[0], (-1)*cHero->getGameObject()->getVelocity()[1]));
    }
    ControlSystem::getInstance()->setInputFactors( Vector2D(1.0f, 1.0f) );

}


// quit
bool CollisionSystem::quit(){
    if(g_CollisionSystem)
        delete[] g_CollisionSystem;
    return ( g_CollisionSystem = NULL );
}


void CollisionSystem::removeCollisionByIdx (int i) {
    colQueue.erase(colQueue.begin()+i);
    cout<<"collision-"+to_string(i)+" has been removed."<<endl;
}
