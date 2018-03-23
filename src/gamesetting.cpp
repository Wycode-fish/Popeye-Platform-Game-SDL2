#include "../include/gamesetting.h"

GameSetting* GameSetting::g_gameSetting = NULL;

GameSetting::ControlSchemes GameSetting::CurrentPlayerControlSchemes[]
            = {GameSetting::ControlSchemes::WASD};

GameSetting* GameSetting::getInstance() {
    if (!g_gameSetting)
        g_gameSetting = new GameSetting();
    return g_gameSetting;
}

GameSetting::GameSetting(){

}


//void GameSetting::initWall () {
//
//    if (!boundary.empty())
//        boundary.clear();
//
//    Wall* top = new Wall( Vector2D( WALL_TOP_INITIAL_POS_X, WALL_TOP_INITIAL_POS_Y ),
//                         Vector2D( WALL_TOP_INITIAL_WIDTH, WALL_TOP_INITIAL_HEIGHT ),
//                         Vector2D( WALL_TOP_NORMAL_X, WALL_TOP_NORMAL_Y ) );
//    Wall* left = new Wall( Vector2D( WALL_LEFT_INITIAL_POS_X, WALL_LEFT_INITIAL_POS_Y ),
//                          Vector2D( WALL_LEFT_INITIAL_WIDTH, WALL_LEFT_INITIAL_HEIGHT ),
//                          Vector2D( WALL_LEFT_NORMAL_X, WALL_LEFT_NORMAL_Y ) );
//    Wall* right = new Wall( Vector2D( WALL_RIGHT_INITIAL_POS_X, WALL_RIGHT_INITIAL_POS_Y ),
//                           Vector2D( WALL_RIGHT_INITIAL_WIDTH, WALL_RIGHT_INITIAL_HEIGHT ),
//                           Vector2D( WALL_RIGHT_NORMAL_X, WALL_RIGHT_NORMAL_Y ) );
//
//    boundary.push_back( top );
//    boundary.push_back( left );
//    boundary.push_back( right );
//}


bool GameSetting::init(){

    cout << "Init GameSetting!\n";

    hero = new Hero();

    initMinions();
    //initWall();
    initPowerUps();
    initBullets();
    level = 1;
    life = 3;

    return true;
}

void GameSetting::reset(){
    init();
}

bool GameSetting::initBullets(){
    bool success = true;
    if ( !bullets.empty() )
        bullets.clear();
    return success;
}

// init PowerUp
bool GameSetting::initPowerUps(){
    bool success = true;

    if( !powerUps.empty() )
        powerUps.clear();

    if (!loadPowerUpPosition()) {
        cout<<"load minion positions failed."<<endl;
        return false;
    }

    for (int i = 0; i < powerUpPositions.size(); i++) {
        PowerUp* temp = new PowerUp();
        temp->setPosition(powerUpPositions[i]);
        powerUps.push_back( temp );
    }

    return success;
}

// load PowerUp
bool GameSetting::loadPowerUpPosition(){
    bool success = true;

    if( !powerUpPositions.empty() )
        powerUpPositions.clear();

    powerUpPositions.push_back( Vector2D( 200.0f, 30.0f ) );

    powerUpPositions.push_back( Vector2D( 800.0f, 40.0f ) );

    return success;
}

bool GameSetting::loadMinionPosition() {
    if( !minionPositions.empty() )
        minionPositions.clear();

    // Read minion position from file
    // string levelFile = "Assets/levels/level" + to_string(level) + ".txt";
    // ifstream fin(levelFile);
    // if (!fin.good()) {
    //   level = 0;
    //   return false;
    // }
    // string s;

    // while (getline(fin,s)) {
    //   if ((s == "") || (s.substr(0,1)==" ")) {
    //     continue;
    //   }
    //   size_t pos = s.find(" ");
    //   float x = stof(s.substr(0, pos));
    //   float y = stof(s.substr(pos+1, string::npos));
    //   minionPositions.push_back(Vector2D(x, y));
    // }

    minionPositions.push_back(Vector2D(120.0f, 40.0f));

    minionPositions.push_back(Vector2D(240.0f, 40.0f));

    return true;
}

bool GameSetting::initMinions(){
    // Init Level One  Array
    bool success = true;
    if( !minions.empty() )
        minions.clear();

    if (!loadMinionPosition()) {
        cout<<"load minion positions failed."<<endl;
        return false;
    }

    for (int i = 0; i < minionPositions.size(); i++) {
        Minion* temp = new Minion();
        temp->setPosition(minionPositions[i]);
        minions.push_back( temp );
    }

    return success;
}



Hero* GameSetting::getHero(){
    return this->hero;
}

vector<Minion*> GameSetting::getMinions(){
    return this->minions;
}

vector<PowerUp*> GameSetting::getPowerUps(){
    return this->powerUps;
}


//vector<Wall*> GameSetting::getBoundary(){
//    return this->boundary;
//}

//long int GameSetting::getScore(){
//    return this->score;
//}

int GameSetting::getLife(){
    return this->life;
}

int GameSetting::getLevel(){
    return this->level;
}

void GameSetting::win(){
    //DisplaySystem::getInstance()->win();
}

void GameSetting::lose(){
    //DisplaySystem::getInstance()->lose();
}

int GameSetting::getPlayerNum() {
    return playerNum;
}
void GameSetting::setPlayerNum(int pn) {
    playerNum = pn;
}

void GameSetting::setLevel( int level ){
    this->level = level;
}

//void GameSetting::setScore( long int score ){
//    this->score = score;
//}

void GameSetting::setLife( int life ){
    this->life = life;
}

bool GameSetting::quit(){
    // Now Do nothing
    bool success = true;
    return success;
}

void GameSetting::update(){
    // Now do nothing
}

void GameSetting::resetHero(){
    hero = new Hero();
}

bool GameSetting::isWinConditionsSatisfied () {
    return (hero->getPosition()[0] >= MAP_WIDTH - 100) && (level == MAXIMUM_LEVEL);
}

void GameSetting::removeMinionByIdx (int i) {
    minions.erase(minions.begin()+i);
    cout<<"minion-"+to_string(i)+" has been removed."<<endl;
}

void GameSetting::removePowerUpByIdx (int i) {
    powerUps.erase(powerUps.begin()+i);
    cout<<"powerUp-"+to_string(i)+" has been removed."<<endl;
}

void GameSetting::addPowerUp(PowerUp* p) {
    powerUps.push_back(p);
    cout<<"powerUp has been added."<<endl;
}

void GameSetting::addBullet(Bullet* b) {
    bullets.push_back(b);
    cout<<"bullet has been added."<<endl;
}

vector<Bullet*> GameSetting::getBullets() {
    return this->bullets;
}

void GameSetting::removeBulletByIdx (int i) {
    bullets.erase(bullets.begin()+i);
    cout<<"bullet-"+to_string(i)+" has been removed."<<endl;
}

void GameSetting::removeDeadBullets(){
    vector<Bullet*> temp;
    for (int i = 0; i < bullets.size(); i++){
        if (bullets[i]->getState())
            temp.push_back(bullets[i]);
    }

    bullets.erase(bullets.begin(), bullets.end());
    bullets.clear();
    bullets.assign(temp.begin(), temp.end());
}

void GameSetting::removeDeadMinions(){
    vector<Minion*> temp;
    for (int i = 0; i < minions.size(); i++){
        if (minions[i]->getState())
            temp.push_back(minions[i]);
    }

    minions.erase(minions.begin(), minions.end());
    minions.clear();
    minions.assign(temp.begin(), temp.end());
}

void GameSetting::removeDeadPowerUps(){
    vector<PowerUp*> temp;
    for (int i = 0; i < powerUps.size(); i++){
        if (powerUps[i]->getState())
            temp.push_back(powerUps[i]);
    }

    powerUps.erase(powerUps.begin(), powerUps.end());
    powerUps.clear();
    powerUps.assign(temp.begin(), temp.end());
}
