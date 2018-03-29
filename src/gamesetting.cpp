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


bool GameSetting::init(){

    cout << "Init GameSetting!\n";
    hero = new Hero();

    TileMapSystem::getInstance()->setCurrentMapId( 0 );

    initMinions();
    initPowerUps();
    initBullets();
    initCollectibles();

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
        cout<<"load powerUp positions failed."<<endl;
        return false;
    }

    for (int i = 0; i < powerUpPositions.size(); i++) {
        PowerUp* temp = new PowerUp();
        temp->setPosition(powerUpPositions[i]);
        powerUps.push_back( temp );
    }

    return success;
}

bool GameSetting::initCollectibles(){
    bool success = true;

    if( !collectibles.empty() )
        collectibles.clear();

    if (!loadCollectiblePosition()) {
        cout<<"load Collectibles positions failed."<<endl;
        return false;
    }

    for (int i = 0; i < collectiblePositions.size(); i++) {
        Collectible* temp = new Collectible();
        temp->setPosition(collectiblePositions[i]);
        collectibles.push_back( temp );
    }

    return success;
}

bool GameSetting::initHero() {
    bool success = true;

    hero = new Hero();

    if (! loadHeroPosition()) {
        cout<<"load hero position failed."<<endl;
        return false;
    }

    return success;
}

bool GameSetting::loadHeroPosition() {
    bool success = true;

    // Read minion position from file
    //generate the file path
//    QString sFile = QApplication::applicationDirPath() + "/Assets/levels/hero/level" + QString::fromStdString(to_string(level)) + ".txt";
//    string levelFile = sFile.toStdString();
    string levelFile = "Assets/levels/hero/level" + to_string(level) + ".txt";
    ifstream fin(levelFile);
    if (!fin.good()) {
      level = 0;
      return false;
    }
    string s;

    while (getline(fin,s)) {
      if ((s == "") || (s.substr(0,1)==" ")) {
        continue;
      }
      size_t pos = s.find(" ");
      float x = stof(s.substr(0, pos));
      float y = stof(s.substr(pos+1, string::npos));
      hero->setPosition(Vector2D(x, y));
    }

    return success;
}

// load PowerUp
bool GameSetting::loadPowerUpPosition(){
    bool success = true;

    if( !powerUpPositions.empty() )
        powerUpPositions.clear();

    // Read powerup position from file
    //generate the file path
//    QString sFile = QApplication::applicationDirPath() + "/Assets/levels/powerups/level" + QString::fromStdString(to_string(level)) + ".txt";
//    string levelFile = sFile.toStdString();
    
    string levelFile = "Assets/levels/powerups/level" + to_string(level) + ".txt";

    ifstream fin(levelFile);
    if (!fin.good()) {
      level = 0;
      return false;
    }
    string s;

    while (getline(fin,s)) {
      if ((s == "") || (s.substr(0,1)==" ")) {
        continue;
      }
      size_t pos = s.find(" ");
      float x = stof(s.substr(0, pos));
      float y = stof(s.substr(pos+1, string::npos));
      powerUpPositions.push_back(Vector2D(x, y));
    }

    // powerUpPositions.push_back( Vector2D( 200.0f, 30.0f ) );

    // powerUpPositions.push_back( Vector2D( 800.0f, 40.0f ) );

    return success;
}

bool GameSetting::loadCollectiblePosition() {

     bool success = true;

    if( !collectiblePositions.empty() )
        collectiblePositions.clear();

    // Read collectible position from file
    //generate the file path
//    QString sFile = QApplication::applicationDirPath() + "/Assets/levels/collectibles/level" + QString::fromStdString(to_string(level)) + ".txt";
//    string levelFile = sFile.toStdString();
    string levelFile = "Assets/levels/collectibles/level" + to_string(level) + ".txt";

    ifstream fin(levelFile);
    if (!fin.good()) {
      level = 0;
      return false;
    }
    string s;

    while (getline(fin,s)) {
      if ((s == "") || (s.substr(0,1)==" ")) {
        continue;
      }
      size_t pos = s.find(" ");
      float x = stof(s.substr(0, pos));
      float y = stof(s.substr(pos+1, string::npos));
      collectiblePositions.push_back(Vector2D(x, y));
    }

    // collectiblePositions.push_back( Vector2D( 160.0f, 30.0f ) );

    // collectiblePositions.push_back( Vector2D( 200.0f, 40.0f ) );

    return success;
}

bool GameSetting::loadMinionPosition() {
    if( !minionPositions.empty() )
        minionPositions.clear();

    // Read minion position from file
    //generate the file path
//    QString sFile = QApplication::applicationDirPath() + "/Assets/levels/minions/level" + QString::fromStdString(to_string(level)) + ".txt";
//    string levelFile = sFile.toStdString();
    string levelFile = "Assets/levels/minions/level" + to_string(level) + ".txt";

    ifstream fin(levelFile);
    if (!fin.good()) {
      level = 0;
      return false;
    }
    string s;

    while (getline(fin,s)) {
      if ((s == "") || (s.substr(0,1)==" ")) {
        continue;
      }
      size_t pos = s.find(" ");
      float x = stof(s.substr(0, pos));
      float y = stof(s.substr(pos+1, string::npos));
      minionPositions.push_back(Vector2D(x, y));
    }

    // minionPositions.push_back(Vector2D(120.0f, 40.0f));

    // minionPositions.push_back(Vector2D(240.0f, 40.0f));

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

vector<Collectible*> GameSetting::getCollectibles(){
    return this->collectibles;
}


//vector<Wall*> GameSetting::getBoundary(){
//    return this->boundary;
//}

long int GameSetting::getScore(){
    return this->score;
}

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

void GameSetting::setScore( long int score ){
    this->score = score;
}

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

void GameSetting::resetHero(Vector2D checkPoint){
    hero = new Hero();
    hero->setPosition(checkPoint);
}

bool GameSetting::isWinConditionsSatisfied () {
    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );
    int mapWidth = currentMap->getWidth() * currentMap->getTileWidth();
    Vector2D passPoint = currentMap->getPassPoint();
    Vector2D heroPos = hero->getPosition();
    float dist = sqrt( pow((heroPos[0] - passPoint[0]), 2.0) + pow( (heroPos[1] - passPoint[1]), 2.0 ) );
    return (dist <= TILE_INITIAL_WIDTH) && (level == MAXIMUM_LEVEL);
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

void GameSetting::initNextLevel(){
    // hero = new Hero();

    level++;

    initHero();
    initMinions();
    initPowerUps();
    initBullets();
    initCollectibles();

    // level++;
}

void GameSetting::initCurrentLevel(){
    // hero = new Hero();

    initHero();
    initMinions();
    initPowerUps();
    initBullets();

    life = 3;
}


void GameSetting::removeDeadCollectibles(){
    vector<Collectible*> temp;
    for (int i = 0; i < collectibles.size(); i++){
        if (collectibles[i]->getState())
            temp.push_back(collectibles[i]);
    }

    collectibles.erase(collectibles.begin(), collectibles.end());
    collectibles.clear();
    collectibles.assign(temp.begin(), temp.end());
}

