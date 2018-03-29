
#include "../include/displaysystem.h"

// Define the static variable
DisplaySystem* DisplaySystem::g_DisplaySystem = NULL;

// getInstance function
DisplaySystem* DisplaySystem::getInstance(){
    if (!g_DisplaySystem)
        g_DisplaySystem = new DisplaySystem();
    return g_DisplaySystem;
}

// Default Constructor
DisplaySystem::DisplaySystem(){
    // Now do nothing
}

// Default Destructor
DisplaySystem::~DisplaySystem(){
    // Now do nothing
}

// Init
bool DisplaySystem::init(){
    // Init all the parameters to the display
    // Initialization flag
    bool success = true;

    // First, init SDL
    if (SDL_Init( SDL_INIT_EVERYTHING ) < 0){
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow( "NinJia Go!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );

        // Check if Window did not create.
        if( gWindow == NULL ){
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        }

        //Create a Renderer to draw on
        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        // Check if Renderer did not create.
        if( gRenderer == NULL ){
            std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
            success = false;
        } else {
            //Initialize renderer color
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                success = false;
            }

            //Initialize SDL_mixer
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                success = false;
            }

            //Initialize SDL_ttf
            if( TTF_Init() == -1 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                success = false;
            }
        }
    }
    // Load Media
    if ( !loadMedia() ){
        std::cout << "Unable to load Media!\n";
        success = false;
    }
    return success;
}


bool DisplaySystem::loadMedia(){
    // Loading success flag
    bool success = true;

    std::cout << "Resource Manager init gRenderer!\n";


    ResourceManager* RM = ResourceManager::getInstance();

    success = RM->init(gRenderer);

    gPowerUpIconTexture = RM->getTextureResource( "texture_powerup_icon" );
    if (gPowerUpIconTexture == NULL){
        std::cout << "Failed to load gPowerUpIcon Texture!\n";
        success = false;
    }


    gMapTexture = RM->getTextureResource( "texture_map_snowscene" );
    if (gMapTexture == NULL ) {
        std::cout << "Failed to load gMapTexture!\n";
        success = false;
    }

    gHeroTexture = RM->getTextureResource( "texture_hero" );
    if ( gHeroTexture == NULL ){
        std::cout << "Failed to load gHeroTexture!\n";
        success = false;
    }

    gMinionTexture = RM->getTextureResource( "texture_minion" );
    if ( gMinionTexture == NULL ){
        std::cout << "Failed to load gMinionTexture!\n";
        success = false;
    }

    gBulletTexture = RM->getTextureResource( "texture_bullet" );
    if ( gMinionTexture == NULL ){
        std::cout << "Failed to load gBulletTexture!\n";
        success = false;
    }

    gPowerUpTexture = RM->getTextureResource( "texture_powerup" );
    if ( gMinionTexture == NULL ){
        std::cout << "Failed to load gPowerUpTexture!\n";
        success = false;
    }

    gCheckPointTexture = RM->getTextureResource("texture_check_point");
    if (gCheckPointTexture == NULL){
        std::cout << "Failed to load gCheckPointTexture!\n";
        success = false;
    }

    gCollectibleTexture = RM->getTextureResource( "texture_collectible" );
    if ( gCollectibleTexture == NULL ){
        std::cout << "Failed to load gCollectibleTexture!\n";
        success = false;
    }

    gFont = RM->getTureTypeFontResource("font_main");
    if ( gFont == NULL ){
        std::cout << "Failed to get gFont in DisplaySystem!\n";
        success = false;
    }



    return success;
}

// update
void DisplaySystem::update(){
    // Clear the Screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);

    updateMapTexture();

    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );
    int mapWidth = currentMap->getWidth() * currentMap->getTileWidth();
    int mapHeight = currentMap->getHeight() * currentMap->getTileHeight();

    this->mapWidth = mapWidth;
    this->mapHeight = mapHeight;


    render();
}

void DisplaySystem::updateMapTexture(){
    int currentMapId = TileMapSystem::getInstance()->getCurrentMapId();
    ResourceManager* RM = ResourceManager::getInstance();
    switch (currentMapId) {
    case 0:
        gMapTexture = RM->getTextureResource("texture_map_snowscene");
        break;
    case 1:
        gMapTexture = RM->getTextureResource("texture_map_kungfu");
        break;
    case 2:
        gMapTexture = RM->getTextureResource("texture_map_old_castle");
        break;
    default:
        break;
    }
}



// render()
void DisplaySystem::render(){


    renderView();

    renderHero();
    
    renderMinions();

    renderBullets();

    renderPowerUps();

    renderCollectibles();

    renderInfo();

    renderCheckPoints();

    SDL_RenderPresent( gRenderer );
}


void DisplaySystem::renderCheckPoints(){
    vector<Vector2D> checkedPointList = PlaySystem::getInstance()->getCheckedPointList();
    int size = checkedPointList.size();
    int num = 0;
    SDL_Rect clip;
    clip.x = 0.0f;
    clip.y = 0.0f;
    clip.w = gCheckPointTexture->getWidth();
    clip.h = gCheckPointTexture->getHeight();
    SDL_Rect shrink;
    shrink.x = 0.0f;
    shrink.y = 0.0f;
    shrink.w = CHECK_POINT_TEXTURE_WIDTH;
    shrink.h = CHECK_POINT_TEXTURE_HEIGHT;
    for (int i = 0; i < size; i++){
        gCheckPointTexture->render( CHECK_POINT_TEXTURE_POSITION_X,
                                    CHECK_POINT_TEXTURE_POSITION_Y + num * CHECK_POINT_TEXTURE_LABEL_SPACE,
                                    gRenderer,
                                    &clip,
                                    &shrink);
        num++;
    }
}




void DisplaySystem::renderView() {

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    int currW = (mapWidth > WINDOW_WIDTH) ? WINDOW_WIDTH : mapWidth;

    int currH = (mapHeight > WINDOW_HEIGHT) ? WINDOW_HEIGHT : mapHeight;

    float targetX = (mapWidth > WINDOW_WIDTH) ? 0.0f : (WINDOW_WIDTH / 2.0 - mapWidth / 2.0);

    float targetY = (mapHeight > WINDOW_HEIGHT) ? 0.0f : (WINDOW_HEIGHT / 2.0 - mapHeight / 2.0);

    gMapTexture->renderStatic (gRenderer,
                            targetX, targetY, currW, currH,
                            cameraPos[0], cameraPos[1], currW, currH);
}



void DisplaySystem::renderHero() {

    Hero* hero = GameSetting::getInstance()->getHero();

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    int frameInPos = hero->getAnimationControl()->getCurrentFrame()*HERO_FRAME_WIDTH;

    int posePos    = (!hero->getIsCol())?
                        (hero->getPoseCode()*2)*HERO_FRAME_HEIGHT:
                            (hero->getPoseCode()*2+1)*HERO_FRAME_HEIGHT;


    gHeroTexture->renderStatic (gRenderer,
                                hero->getPosition()[0] - HERO_WIDTH_INITIAL / 2 - cameraPos[0],
                                hero->getPosition()[1] - HERO_HEIGHT_INITIAL / 2 - cameraPos[1],
                                HERO_WIDTH_INITIAL, HERO_HEIGHT_INITIAL,
                                frameInPos,
                                posePos,
                                HERO_FRAME_WIDTH, HERO_FRAME_HEIGHT);
}


void DisplaySystem::renderMinions() {

    vector<Minion*> minions = GameSetting::getInstance()->getMinions();

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    for (int i = 0; i < minions.size(); i++){

        if ( minions[i]->getState() == IS_ALIVE ){

            int frameInPos = minions[i]->getAnimationControl()->getCurrentFrame()*MINION_FRAME_WIDTH; 

            int posePos    = minions[i]->getPoseCode()*MINION_FRAME_HEIGHT;


            gMinionTexture->renderStatic (gRenderer,
                                            minions[i]->getPosition()[0] - MINION_INITIAL_WIDTH / 2.0 - cameraPos[0],
                                            minions[i]->getPosition()[1] - MINION_INITIAL_HEIGHT / 2.0 - cameraPos[1],
                                            MINION_INITIAL_WIDTH, MINION_INITIAL_HEIGHT,
                                            frameInPos, 
                                            posePos, 
                                            MINION_FRAME_WIDTH, MINION_FRAME_HEIGHT);
        }
    }
}


void DisplaySystem::renderBullets() {

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    vector<Bullet*> bullets = GameSetting::getInstance()->getBullets();

    for (int i = 0; i < bullets.size(); i++){

        if ( bullets[i]->getState() == IS_ALIVE ){

            int frameInPos = bullets[i]->getAnimationControl()->getCurrentFrame()*BULLET_FRAME_WIDTH; 

            int posePos    = bullets[i]->getPoseCode()*BULLET_FRAME_HEIGHT;

            gBulletTexture->renderStatic (gRenderer,
                                    bullets[i]->getPosition()[0] - BULLET_INITIAL_WIDTH / 2.0 - cameraPos[0],
                                    bullets[i]->getPosition()[1] - BULLET_INITIAL_HEIGHT / 2.0 - cameraPos[1],
                                    BULLET_INITIAL_WIDTH, BULLET_INITIAL_HEIGHT,
                                    frameInPos, 
                                    posePos,
                                    BULLET_FRAME_WIDTH, BULLET_FRAME_HEIGHT);

        }

    }
}


void DisplaySystem::renderPowerUps() {

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    vector<PowerUp*> powerUps = GameSetting::getInstance()->getPowerUps();

    for (int i = 0; i < powerUps.size(); i++){

        if ( powerUps[i]->getState() == IS_ALIVE ) {

            int frameInPos = powerUps[i]->getAnimationControl()->getCurrentFrame()*POWERUP_FRAME_WIDTH;

            int posePos    = powerUps[i]->getPoseCode()*POWERUP_FRAME_HEIGHT;

            gPowerUpTexture->renderStatic (gRenderer,
                                    powerUps[i]->getPosition()[0] - POWERUP_INITIAL_WIDTH / 2.0 - cameraPos[0],
                                    powerUps[i]->getPosition()[1] - POWERUP_INITIAL_HEIGHT / 2.0 - cameraPos[1],
                                    POWERUP_INITIAL_WIDTH, POWERUP_INITIAL_HEIGHT,
                                    frameInPos, 
                                    posePos, 
                                    POWERUP_FRAME_WIDTH, POWERUP_FRAME_HEIGHT);
        }


    }
}

bool DisplaySystem::loadInfoTexture(){
    bool success = true;
    int life = GameSetting::getInstance()->getLife();
    int level = GameSetting::getInstance()->getLevel();
    long int score = GameSetting::getInstance()->getScore();
    int powerCode = GameSetting::getInstance()->getHero()->getPowerCode();

    stringstream lifeText;
    stringstream levelText;
    stringstream stateText;
    stringstream scoreText;
    string powerText = "";

    switch (powerCode) {
    case POWERUP_CODE_FIRE:{
        powerText = ResourceManager::getInstance()->getCurrentLanguageMap()["fire"];
        break;
    }
    case POWERUP_CODE_FLOAT:{
        powerText = ResourceManager::getInstance()->getCurrentLanguageMap()["fly"];
        break;
    }
    case POWERUP_CODE_SPEED_UP:{
        powerText = ResourceManager::getInstance()->getCurrentLanguageMap()["speedup"];
        break;
    }
    default:
        break;
    }
    // Set life Text to be rendered
    lifeText.str( "" );
    lifeText << ResourceManager::getInstance()->getCurrentLanguageMap()["life"] << " : " << life;
    if ( !gLifeTextTexture->loadFromRenderedText( lifeText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load life Text Texture!\n";
    }

    // Set level Text to be rendered
    levelText.str( "" );
    levelText << ResourceManager::getInstance()->getCurrentLanguageMap()["level"] << " : " << level;
    if ( !gLevelTextTexture->loadFromRenderedText( levelText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load level Text Texture!\n";
    }

    // Set state Text to be rendered
    stateText.str( "" );
    stateText << ResourceManager::getInstance()->getCurrentLanguageMap()["state"] << " : " << powerText;
    if ( !gStateTextTexture->loadFromRenderedText( stateText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load state Text Texture!\n";
    }

    // Set score Text to be rendered
    scoreText.str( "" );
    scoreText << ResourceManager::getInstance()->getCurrentLanguageMap()["score"] << " : " << score;
    if ( !gScoreTextTexture->loadFromRenderedText( scoreText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load score Text Texture!\n";
    }
    return success;
}

void DisplaySystem::renderInfo(){
    if( !loadInfoTexture() ){
        cout << "Unable to load info texture!\n";
        return;
    }

    int powerCode = GameSetting::getInstance()->getHero()->getPowerCode();

    gLifeTextTexture->render(LIFE_TEXTURE_POSITION_X, LIFE_TEXTURE_POSITION_Y, gRenderer);

    gLevelTextTexture->render(LEVEL_TEXTURE_POSITION_X, LEVEL_TEXTURE_POSITION_Y, gRenderer);

    gStateTextTexture->render(STATE_TEXTURE_POSITION_X, STATE_TEXTURE_POSITION_Y, gRenderer);

    gScoreTextTexture->render(SCORE_TEXTURE_POSITION_X, SCORE_TEXTURE_POSITION_Y, gRenderer);

    SDL_Rect shrink;
    shrink.x = 0.0f;
    shrink.y = 0.0f;
    shrink.w = POWERUP_ICON_TEXTURE_WIDTH;
    shrink.h = POWERUP_ICON_TEXTURE_HEIGHT;

//    switch (powerCode) {
//    case POWERUP_CODE_SPEED_UP:{
//        SDL_Rect clip;
//        clip.x = POWERUP_ICON_SPEED_UP_POSITION_X;
//        clip.y = POWERUP_ICON_SPEED_UP_POSITION_Y;
//        clip.w = POWERUP_ICON_WIDTH;
//        clip.h = POWERUP_ICON_HEIGHT;
//        gPowerUpIconTexture->render( POWERUP_ICON_TEXTURE_POSITION_X,
//                                     POWERUP_ICON_TEXTURE_POSITION_Y,
//                                     gRenderer,
//                                     &clip,
//                                     &shrink);
//        break;
//    }
//    case POWERUP_CODE_FLOAT:{
//        SDL_Rect clip;
//        clip.x = POWERUP_ICON_FLOAT_POSITION_X;
//        clip.y = POWERUP_ICON_FLOAT_POSITION_Y;
//        clip.w = POWERUP_ICON_WIDTH;
//        clip.h = POWERUP_ICON_HEIGHT;
//        gPowerUpIconTexture->render( POWERUP_ICON_TEXTURE_POSITION_X,
//                                     POWERUP_ICON_TEXTURE_POSITION_Y,
//                                     gRenderer,
//                                     &clip,
//                                     &shrink);
//        break;
//    }
//    case POWERUP_CODE_FIRE:{
//        SDL_Rect clip;
//        clip.x = POWERUP_ICON_FIRE_POSITION_X;
//        clip.y = POWERUP_ICON_FIRE_POSITION_Y;
//        clip.w = POWERUP_ICON_WIDTH;
//        clip.h = POWERUP_ICON_HEIGHT;
//        gPowerUpIconTexture->render( POWERUP_ICON_TEXTURE_POSITION_X,
//                                     POWERUP_ICON_TEXTURE_POSITION_Y,
//                                     gRenderer,
//                                     &clip,
//                                     &shrink);
//        break;
//    }
//    default:
//        break;
//    }

}

void DisplaySystem::renderCollectibles() {

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    vector<Collectible*> collectibles = GameSetting::getInstance()->getCollectibles();

    for (int i = 0; i < collectibles.size(); i++){

        if ( collectibles[i]->getState() == IS_ALIVE ) {

            int frameInPos = collectibles[i]->getAnimationControl()->getCurrentFrame()*COLLECTIBLE_FRAME_WIDTH;

            int posePos    = collectibles[i]->getPoseCode()*COLLECTIBLE_FRAME_HEIGHT;

            gCollectibleTexture->renderStatic (gRenderer,
                                    collectibles[i]->getPosition()[0] - COLLECTIBLE_INITIAL_WIDTH / 2.0 - cameraPos[0],
                                    collectibles[i]->getPosition()[1] - COLLECTIBLE_INITIAL_HEIGHT / 2.0 - cameraPos[1],
                                    COLLECTIBLE_INITIAL_WIDTH, COLLECTIBLE_INITIAL_HEIGHT,
                                    frameInPos,
                                    posePos,
                                    COLLECTIBLE_FRAME_WIDTH, COLLECTIBLE_FRAME_HEIGHT);
        }


    }
}

MENU_MESSAGE DisplaySystem::renderMainMenu(){
    MainMenu* mainMenu = new MainMenu( gRenderer );
    mainMenu->show();
    return mainMenu->accept();
}

MENU_MESSAGE DisplaySystem::renderPauseMenu(){
    PauseMenu* pauseMenu = new PauseMenu( gRenderer );
    pauseMenu->show();
    return pauseMenu->accept();
}

MENU_MESSAGE DisplaySystem::renderPassMenu(){
    PassMenu* passMenu = new PassMenu( gRenderer );
    passMenu->show();
    return passMenu->accept();
}


// renderLose
MENU_MESSAGE DisplaySystem::renderLoseMenu(){
    LoseMenu* loseMenu = new LoseMenu( gRenderer );
    loseMenu->show();
    return loseMenu->accept();
}

// renderWin
MENU_MESSAGE DisplaySystem::renderWinMenu(){
    WinMenu* winMenu = new WinMenu( gRenderer );
    winMenu->show();
    return winMenu->accept();
}

// quit
bool DisplaySystem::quit(){
    bool success = true;
    // Destroy Renderer
    SDL_DestroyRenderer( gRenderer );
    //Destroy window
    SDL_DestroyWindow( gWindow );
    // Point gWindow to NULL to ensure it points to nothing.
    gRenderer = NULL;
    gWindow = NULL;


    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL subsystems
    SDL_Quit();
    return success;
}


SDL_Window* DisplaySystem::getSDLWindow(){
    return this->gWindow;
}

SDL_Renderer* DisplaySystem::getSDLRenderer(){
    return this->gRenderer;
}


