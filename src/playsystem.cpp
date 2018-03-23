#include "../include/playsystem.h"

PlaySystem* PlaySystem::g_playSystem = NULL;

// getInstance function
PlaySystem* PlaySystem::getInstance(){
    if (!g_playSystem)
        g_playSystem = new PlaySystem();
    return g_playSystem;
}

// Default destructor
PlaySystem::~PlaySystem(){
    // Now do nothing
}

// Default constructor
PlaySystem::PlaySystem(){
    // Now do nothing
}

// init
bool PlaySystem::init(){
    // Now do nothing
    bool success = true;
    return success;
}


/*************************.    PlaySystem Update   *************************/
void PlaySystem::update(){

    if (isGameOver())
        gameOver();

    if (isHeroOver()) return;

    if (isHeroWin()) return;

    bulletUpdate();

    minionsUpdate();

    powerUpUpdate();

    heroUpdate();


    if (SDL_GetTicks() % 10000 == 0) {

        cout<<"10s passed, PowerUp Generating..."<<endl;

        powerUpGeneration();
    }

}


/*************************.    Hero Out of Scene, Game's Over.   *************************/
bool PlaySystem::isHeroOver() {

    Hero* hero = GameSetting::getInstance()->getHero();



    if ( hero->getPosition()[1] > MAP_HEIGHT )
        hero->setState( IS_DEAD );
    // Game Over Operations
    if ( hero->getState() == IS_DEAD ){
        // Game Over
        std::cout << "Game Over!\n";
        if( GameSetting::getInstance()->getLife() != 0 ){
            GameSetting::getInstance()->setLife( GameSetting::getInstance()->getLife() - 1 );// Lose one life
            GameSetting::getInstance()->resetHero();
        } else{
            this->loseState = true;
        }



        return true;
    }

    return false;
}

/*************************.   Check if the game is over, and execute game over.   *************************/

bool PlaySystem::isGameOver(){

    int life = GameSetting::getInstance()->getLife();

    if (life <= 0){
        cout << "Life" << life << endl;
        cout << "Game Over!\n";
        return true;
    } 
    else {
        cout << "Still Alive !\n";
    }

    return false;
}


void PlaySystem::gameOver(){
    SDL_Delay( 1000 );
    GameSetting::getInstance()->reset();
}


/*************************.    Hero Satisfies Win Condition, Next Level.   *************************/
bool PlaySystem::isHeroWin() {
    bool isWin = GameSetting::getInstance()->isWinConditionsSatisfied ();
    if (isWin){
        std::cout << "You Win!\n";
        GameSetting::getInstance()->setLevel( GameSetting::getInstance()->getLevel() + 1 );// get one level up
        this->winState = true;
        return true;
    }

    return false;
}


/*************************.    Game's not Over. GameObject Updates   *************************/

// For PowerUps
// 1. check live/dead state
void PlaySystem::powerUpUpdate() {

    vector<PowerUp*> puList = GameSetting::getInstance()->getPowerUps();

    for (int i=0; i<puList.size(); i++) {

        if ( puList[i]->getPosition()[1] > MAP_HEIGHT )
            puList[i]->setState( IS_DEAD );

//        if (!puList[i]->getState()) {
//            cout<<"powerUp-"+to_string(i)+" out"<<endl;
//            delete puList[i];
//            GameSetting::getInstance()->removePowerUpByIdx(i);
//            continue;
//        }

        powerUpPoseUpdate(puList[i]);

        powerUpVelocityUpdate(puList[i]);

        powerUpPositionUpdate(puList[i]);
    }

    GameSetting::getInstance()->removeDeadPowerUps();

    // update other things

}

void PlaySystem::powerUpPoseUpdate(PowerUp* p){
    // Just Leave here

    p->getAnimationControl()->onAnimate();
}

void PlaySystem::powerUpVelocityUpdate(PowerUp* p){

    p->setVelocity( Vector2D( p->getVelocity()[0] + p->getAcceleration()[0], p->getVelocity()[1] + p->getAcceleration()[1]));

    if (p->getVelocity()[0] > p->getMaxVelocity()[0])
        p->setVelocity( Vector2D( p->getMaxVelocity()[0], p->getVelocity()[1]));

    else if (p->getVelocity()[0] < (-1)*p->getMaxVelocity()[0])
        p->setVelocity( Vector2D( (-1)*p->getMaxVelocity()[0], p->getVelocity()[1]));

    if (p->getVelocity()[1] > p->getMaxVelocity()[1])
        p->setVelocity( Vector2D( p->getVelocity()[0], p->getMaxVelocity()[1]));

    else if (p->getVelocity()[1] < (-1)*p->getMaxVelocity()[1])
        p->setVelocity( Vector2D( p->getVelocity()[0], (-1)*p->getMaxVelocity()[1]));

    // Acceleration Update
    //p->setAcceleration( Vector2D( p->getAcceleration()[0], GRAVITY ) );
}

void PlaySystem::powerUpPositionUpdate(PowerUp* p){
    p->setPosition( Vector2D( p->getPosition()[0] + p->getVelocity()[0] * 0.05, p->getPosition()[1] + p->getVelocity()[1] * 0.05));

    if (p->getPosition()[0] < POWERUP_INITIAL_WIDTH / 2.0f)
        p->setPosition( Vector2D( POWERUP_INITIAL_WIDTH / 2.0f, p->getPosition()[1] ) );
    if (p->getPosition()[0] > MAP_WIDTH - POWERUP_INITIAL_WIDTH / 2.0f)
        p->setPosition( Vector2D( MAP_WIDTH - POWERUP_INITIAL_WIDTH / 2.0f, p->getPosition()[1] ) );
    if (p->getPosition()[1] < POWERUP_INITIAL_HEIGHT / 2.0f)
        p->setPosition( Vector2D( p->getPosition()[0], POWERUP_INITIAL_HEIGHT / 2.0f ) );
    if (p->getPosition()[1] > MAP_HEIGHT - POWERUP_INITIAL_HEIGHT / 2.0f)
        p->setPosition( Vector2D( p->getPosition()[0], MAP_HEIGHT - POWERUP_INITIAL_HEIGHT / 2.0f ) );

}

void PlaySystem::bulletUpdate() {

    vector<Bullet*> bList = GameSetting::getInstance()->getBullets();

    for (int i=0; i<bList.size(); i++) {

        if ( bList[i]->getPosition()[0] > MAP_WIDTH )
            bList[i]->setState( IS_DEAD );

//        if (!bList[i]->getState()) {
//            cout<<"powerUp-"+to_string(i)+" out"<<endl;
//            //delete bList[i];
//            GameSetting::getInstance()->removeBulletByIdx(i);
//            continue;
//        }

        bulletVelocityUpdate(bList[i]);

        bulletPositionUpdate(bList[i]);

        bList[i]->getAnimationControl()->onAnimate();

    }

    GameSetting::getInstance()->removeDeadBullets();
}

void PlaySystem::bulletVelocityUpdate(Bullet* b){
    // Do nothing
}

void PlaySystem::bulletPositionUpdate(Bullet* b){
    b->setPosition( Vector2D( b->getPosition()[0] + b->getVelocity()[0], b->getPosition()[1] ) );
}


// For Hero (live/dead has been checked before)
// 1. check isColValid
// 2. check powerCode
// 3. update position
// 4. update velocity
void PlaySystem::heroUpdate() {

    cout<<"hero update enter."<<endl;

    heroIsColUpdate();

    heroPoseUpdate();

    heroFireUpdate();

    heroPowerUpdate();

    heroVelocityUpdate();

    heroPositionUpdate();

    heroReset();
}


void PlaySystem::heroReset() {

    // ACCELERATION REFRESH
    Hero* hero = GameSetting::getInstance()->getHero();

    hero->setAcceleration( Vector2D( hero->getAcceleration()[0], GRAVITY));

    //hero->setVelocity( Vector2D( 0.0f, hero->getVelocity()[1]) );

    ControlSystem::getInstance()->setInput( GameSetting::getInstance()->getPlayerNum() - 1, new Vector2D(0.0f, 0.0f) );

}
// For Minions
// 1. check live/dead state
// 2. check isColStop
// 3. update position
// 4. update velocity
void PlaySystem::minionsUpdate() {

    vector<Minion*> minions = GameSetting::getInstance()->getMinions();

    for (int i=0; i<minions.size(); i++) {

        if (!minionIsLiveUpdate(minions[i], i)) {

            if (!minions[i]->getState()) {             // 1
//                cout<<"minions-"+to_string(i)+" out"<<endl;
//                delete minions[i];
//                GameSetting::getInstance()->removeMinionByIdx(i);
//                continue;
            }
        };

        minionIsColUpdate(minions[i]);


        minionPoseUpdate(minions[i]);

        minionVelocityUpdate(minions[i]);

        minionPositionUpdate(minions[i]);

    }

    GameSetting::getInstance()->removeDeadMinions();
}


// PowerUp generation;
void PlaySystem::powerUpGeneration () {
    PowerUp* ptr = new PowerUp();
    GameSetting::getInstance()->addPowerUp(ptr);
}




/*************************.    Minion Update Helper Function  *************************/
bool PlaySystem::minionIsLiveUpdate(Minion* m, int i) {

    if ( m->getPosition()[1] > MAP_HEIGHT )
        m->setState( IS_DEAD );

    return m->getState();
}


void PlaySystem::minionIsColUpdate(Minion* m) {

    if (m->getIsCol()) {

        if (m->getLastColTime() + MINION_COLLISION_STOP_TIME < SDL_GetTicks()){
            m->setIsCol(false);
        }
    }
}

void PlaySystem::minionPoseUpdate(Minion* m) {

    if (m->getVelocity()[0]<0 && m->getVelocity()[1] == 0) {

        m->setPoseCode (MINION_POSE_MOVE_LEFT);
    }

    else if (m->getVelocity()[0]>0 && m->getVelocity()[1] == 0) {

        m->setPoseCode (MINION_POSE_MOVE_RIGHT);
    }



    // if (m->getVelocity() == Vector2D(0,0) && m->getPoseCode()%2 == 0) {
    //     m->setPoseCode (MINION_POSE_STAND_LEFT);
    // }

    // if (m->getVelocity() == Vector2D(0,0) && m->getPoseCode()%2 == 1) {
    //     m->setPoseCode (MINION_POSE_STAND_RIGHT);
    // }


    // if ( (m->getPoseCode()%2 == 1 && m->getVelocity()[1] < 0) || (m->getVelocity()[0] > 0 && m->getVelocity()[1] > 0)) {
    //     m->setPoseCode (MINION_POSE_JUMP_RIGHT);
    // }

    // if ( (m->getPoseCode()%2 == 0 && m->getVelocity()[1] < 0) ||
    //     (m->getVelocity()[0] < 0 && m->getVelocity()[1] > 0))
    // {
    //     m->setPoseCode (MINION_POSE_JUMP_LEFT);
    // }

    // if ( (m->getPoseCode()%2 == 1 && m->getVelocity()[1] > 0) ||
    //     (m->getVelocity()[0] > 0 && m->getVelocity()[1] > 0))
    // {
    //     m->setPoseCode (MINION_POSE_FALL_RIGHT);
    // }

    // if ( (m->getPoseCode()%2 == 0 && m->getVelocity()[1] > 0) ||
    //     (m->getVelocity()[0] < 0 && m->getVelocity()[1] > 0))
    // {
    //     m->setPoseCode (MINION_POSE_FALL_LEFT);
    // }

    m->getAnimationControl()->onAnimate();
}

void PlaySystem::minionPositionUpdate(Minion* m) {

    if (m->getIsCol()) return;

    else{
        m->setPosition( Vector2D( m->getPosition()[0] + m->getVelocity()[0] * MINION_POS_MOVE_FACTOR, m->getPosition()[1] + m->getVelocity()[1] * MINION_POS_MOVE_FACTOR));

        if (m->getPosition()[0] < MINION_INITIAL_WIDTH / 2.0f)
            m->setPosition( Vector2D( MINION_INITIAL_WIDTH / 2.0f, m->getPosition()[1] ) );
        if (m->getPosition()[0] > MAP_WIDTH - MINION_INITIAL_WIDTH / 2.0f)
            m->setPosition( Vector2D( MAP_WIDTH - MINION_INITIAL_WIDTH / 2.0f, m->getPosition()[1] ) );
        if (m->getPosition()[1] < MINION_INITIAL_HEIGHT / 2.0f)
            m->setPosition( Vector2D( m->getPosition()[0], MINION_INITIAL_HEIGHT / 2.0f ) );
        if (m->getPosition()[1] > MAP_HEIGHT - MINION_INITIAL_HEIGHT / 2.0f)
            m->setPosition( Vector2D( m->getPosition()[0], MAP_HEIGHT - MINION_INITIAL_HEIGHT / 2.0f ) );
    }
}


void PlaySystem::minionVelocityUpdate(Minion* m) {

    m->setVelocity( Vector2D( m->getVelocity()[0] + m->getAcceleration()[0], m->getVelocity()[1] + m->getAcceleration()[1]));

    if (m->getVelocity()[0] > m->getMaxVelocity()[0])
        m->setVelocity( Vector2D( m->getMaxVelocity()[0], m->getVelocity()[1]));

    else if (m->getVelocity()[0] < (-1)*m->getMaxVelocity()[0])
        m->setVelocity( Vector2D( (-1)*m->getMaxVelocity()[0], m->getVelocity()[1]));

    if (m->getVelocity()[1] > m->getMaxVelocity()[1])
        m->setVelocity( Vector2D( m->getVelocity()[0], m->getMaxVelocity()[1]));

    else if (m->getVelocity()[1] < (-1)*m->getMaxVelocity()[1])
        m->setVelocity( Vector2D( m->getVelocity()[0], (-1)*m->getMaxVelocity()[1]));

    // Map Boundary Cap
    if ((m->getPosition()[0] <= MINION_INITIAL_WIDTH / 2.0f) || (m->getPosition()[0] >= MAP_WIDTH - MINION_INITIAL_WIDTH / 2.0f))
            m->setVelocity( Vector2D( (-1)*m->getVelocity()[0], m->getVelocity()[1] ) );
    if ((m->getPosition()[1] < MINION_INITIAL_HEIGHT / 2.0f) || (m->getPosition()[1] > MAP_HEIGHT - MINION_INITIAL_HEIGHT / 2.0f))
            m->setVelocity( Vector2D( m->getVelocity()[0], (-1)*m->getVelocity()[1] ) );
        
    // ACCELERATION REFRESH
    m->setAcceleration( Vector2D( m->getAcceleration()[0], GRAVITY));
}



/*************************.    Hero Update Helper Function  *************************/
void PlaySystem::heroIsColUpdate() {

    cout<<"hero collision update enter."<<endl;

    Hero* hero = GameSetting::getInstance()->getHero();

    if (hero->getIsCol()) {
        if (hero->getLastColTime() + HERO_COLLISION_INVALID_TIME < SDL_GetTicks()){

            hero->setIsCol(false);
        }
    }
}

void PlaySystem::heroPowerUpdate() {

//    cout<<"hero powerup update enter."<<endl;

    Hero* hero = GameSetting::getInstance()->getHero();

    switch (hero->getPowerCode()) {

        case POWERUP_CODE_SPEED_UP:
            hero->setMaxVelocity( Vector2D(POWERUP_SPEED_UP_MAX_SPEED, MAX_VELOCITY_Y) );
            break;

        case POWERUP_CODE_FLOAT:
            hero->setAcceleration( Vector2D(hero->getAcceleration()[0], POWERUP_FLOAT_GRAVITY));
            break;

        default:
            cout<<"Hero Has No Power Yet."<<endl;
    }
}

void PlaySystem::heroPoseUpdate() {

//    cout<<"hero pose update enter."<<endl;

    Hero* hero = GameSetting::getInstance()->getHero();

    Vector2D* input = ControlSystem::getInstance()->getInputs( GameSetting::getInstance()->getPlayerNum() - 1 );

    if (hero->getVelocity() == Vector2D(0,0) && hero->getPoseCode()%2 == 0) {
        hero->setPoseCode (HERO_POSE_STAND_RIGHT);
    }

    else if (hero->getVelocity() == Vector2D(0,0) && hero->getPoseCode()%2 == 1) {
        hero->setPoseCode (HERO_POSE_STAND_LEFT);
    }

    else if (hero->getVelocity()[0]>0 && hero->getVelocity()[1] == 0) {
        hero->setPoseCode (HERO_POSE_MOVE_RIGHT);
    }

    else if (hero->getVelocity()[0]<0 && hero->getVelocity()[1] == 0) {
        hero->setPoseCode (HERO_POSE_MOVE_LEFT);
    }

    else if ( (hero->getPoseCode()%2 == 0 && hero->getVelocity()[1] < 0) ||
             (hero->getVelocity()[0] > 0 && hero->getVelocity()[1] < 0)) {
        hero->setPoseCode (HERO_POSE_JUMP_RIGHT);
    }

    else if ( (hero->getPoseCode()%2 == 1 && hero->getVelocity()[1] < 0) ||
             (hero->getVelocity()[0] < 0 && hero->getVelocity()[1] < 0)) {
        hero->setPoseCode (HERO_POSE_JUMP_LEFT);
    }

    else if ( (hero->getPoseCode()%2 == 0 && hero->getVelocity()[1] > 0) ||
             (hero->getVelocity()[0] > 0 && hero->getVelocity()[1] > 0)) {
        hero->setPoseCode (HERO_POSE_STAND_RIGHT);
    }

    else if ( (hero->getPoseCode()%2 == 1 && hero->getVelocity()[1] > 0) ||
             (hero->getVelocity()[0] < 0 && hero->getVelocity()[1] > 0)) {
        hero->setPoseCode (HERO_POSE_STAND_LEFT);
    }

    hero->getAnimationControl()->onAnimate();
}

void PlaySystem::heroFireUpdate() {

//    cout<<"hero fire update enter."<<endl;

    Hero* hero = GameSetting::getInstance()->getHero();

    bool isFireinput = ControlSystem::getInstance()->getIsFireInput( GameSetting::getInstance()->getPlayerNum() - 1 );

    if (isFireinput == true) {

        bool isDirRight = (hero->getPoseCode()%2 == 1)?true: false;

        cout << "Get Fire Input !\n";

        Bullet* b = new Bullet(hero->getPosition(), (isDirRight)?Vector2D((-1)*BULLET_INITIAL_VELOCITY_X,0):Vector2D(BULLET_INITIAL_VELOCITY_X,0));

        GameSetting::getInstance()->addBullet(b);
    }
    ControlSystem::getInstance()->setIsFireInput( GameSetting::getInstance()->getPlayerNum() - 1 );
}


void PlaySystem::heroPositionUpdate() {

    cout<<"hero position update enter."<<endl;

    Hero* hero = GameSetting::getInstance()->getHero();

    hero->setPosition( Vector2D( hero->getPosition()[0] + hero->getVelocity()[0]*HERO_POS_MOVE_FACTOR,
                                hero->getPosition()[1] + hero->getVelocity()[1]*HERO_POS_MOVE_FACTOR));

    if (hero->getPosition()[0] < HERO_WIDTH_INITIAL / 2.0f)
        hero->setPosition( Vector2D( HERO_WIDTH_INITIAL / 2.0f, hero->getPosition()[1] ) );

    if (hero->getPosition()[0] > MAP_WIDTH - HERO_WIDTH_INITIAL / 2.0f)
        hero->setPosition( Vector2D( MAP_WIDTH - HERO_WIDTH_INITIAL / 2.0f, hero->getPosition()[1] ) );
    
    if (hero->getPosition()[1] < HERO_HEIGHT_INITIAL / 2.0f)
        hero->setPosition( Vector2D( hero->getPosition()[0], HERO_HEIGHT_INITIAL / 2.0f ) );
    
    if (hero->getPosition()[1] > MAP_HEIGHT - HERO_HEIGHT_INITIAL / 2.0f)
        hero->setPosition( Vector2D( hero->getPosition()[0], MAP_HEIGHT - HERO_HEIGHT_INITIAL / 2.0f ) );


}

void PlaySystem::heroVelocityUpdate () {

    cout<<"hero velocity update enter."<<endl;

    Hero* hero = GameSetting::getInstance()->getHero();

    int currPowerCode = hero->getPowerCode();

    if (currPowerCode == POWERUP_CODE_FLOAT) {
        
    }

    //ControlSystem::getInstance()->setInput( GameSetting::getInstance()->getPlayerNum() - 1, new Vector2D(-1.0f, 0.0f) );

    Vector2D* input = ControlSystem::getInstance()->getInputs( GameSetting::getInstance()->getPlayerNum() - 1 );


    float velocityY = (hero->getIsFloat())?hero->getVelocity()[1] + hero->getAcceleration()[1] * (1.0/FPS):
                        hero->getVelocity()[1] +
                            hero->getAcceleration()[1] * (1.0/FPS) +
                                (*input)[1]*100;

    float velocityX = hero->getVelocity()[0] +
                        hero->getAcceleration()[0] * (1.0/FPS) +
                            (*input)[0]*100;

    hero->setVelocity( Vector2D( velocityX, velocityY));


    if (hero->getVelocity()[0] > hero->getMaxVelocity()[0])
        hero->setVelocity( Vector2D( hero->getMaxVelocity()[0], hero->getVelocity()[1]));

    else if (hero->getVelocity()[0] < (-1)*hero->getMaxVelocity()[0])
        hero->setVelocity( Vector2D( (-1)*hero->getMaxVelocity()[0], hero->getVelocity()[1]));

    if (hero->getVelocity()[1] > hero->getMaxVelocity()[1])
        hero->setVelocity( Vector2D( hero->getVelocity()[0], hero->getMaxVelocity()[1]));

    else if (hero->getVelocity()[1] < (-1)*hero->getMaxVelocity()[1])
        hero->setVelocity( Vector2D( hero->getVelocity()[0], (-1)*hero->getMaxVelocity()[1]));

}

// quit
bool PlaySystem::quit(){
    if (!g_playSystem)
        delete[] g_playSystem;
    return (g_playSystem = NULL);
}

// isWin
bool PlaySystem::isWin(){
    return this->winState;
}
// isLose
bool PlaySystem::isLose(){
    return this->loseState;
}

// reset the win/lose state
void PlaySystem::reset(){
    this->winState = false;
    this->loseState = false;
}

