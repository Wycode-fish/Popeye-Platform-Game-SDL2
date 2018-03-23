
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
        gWindow = SDL_CreateWindow( "BreakOut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );

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


    gMapTexture = RM->getTextureResource( "texture_map" );
    if (gMapTexture == NULL ) {
        std::cout << "Failed to load gHeroTexture!\n";
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
        std::cout << "Failed to load gMinionTexture!\n";
        success = false;
    }

    gPowerUpTexture = RM->getTextureResource( "texture_powerup" );
    if ( gMinionTexture == NULL ){
        std::cout << "Failed to load gMinionTexture!\n";
        success = false;
    }

    return success;
}

// update
void DisplaySystem::update(){
    // Clear the Screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);


    render();
}



// render()
void DisplaySystem::render(){


    renderView();

    renderHero();
    
    renderMinions();

    renderBullets();

    renderPowerUps();

    SDL_RenderPresent( gRenderer );
}




void DisplaySystem::renderView() {

    Vector2D cameraPos = Camera::getInstance()->getCameraPos();

    int currW = (mapWidth > WINDOW_WIDTH) ? WINDOW_WIDTH : mapWidth;

    int currH = (mapHeight > WINDOW_HEIGHT) ? WINDOW_HEIGHT : mapHeight;

    gMapTexture->renderStatic (gRenderer,
                            0.0f, 0.0f, currW, currH,
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
                                            minions[i]->getPosition()[1] - MINION_INITIAL_HEIGHT / 2.0 - cameraPos[0],
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

            int posePos    = bullets[i]->getPoseCode();

            gBulletTexture->renderStatic (gRenderer,
                                    bullets[i]->getPosition()[0] - BULLET_INITIAL_WIDTH / 2.0 - cameraPos[0],
                                    bullets[i]->getPosition()[1] - BULLET_INITIAL_HEIGHT / 2.0 - cameraPos[0],
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

            int posePos    = powerUps[i]->getPoseCode();

            gPowerUpTexture->renderStatic (gRenderer,
                                    powerUps[i]->getPosition()[0] - POWERUP_INITIAL_WIDTH / 2.0 - cameraPos[0],
                                    powerUps[i]->getPosition()[1] - POWERUP_INITIAL_HEIGHT / 2.0 - cameraPos[0],
                                    POWERUP_INITIAL_WIDTH, POWERUP_INITIAL_HEIGHT,
                                    frameInPos, 
                                    posePos, 
                                    POWERUP_FRAME_WIDTH, POWERUP_FRAME_HEIGHT);
        }


    }
}

bool DisplaySystem::renderMainMenu(){
    MainMenu* mainMenu = new MainMenu( gRenderer );
    mainMenu->show();
    if(mainMenu->accept() == MENU_QUIT)
        return false;
    return true;
}

bool DisplaySystem::renderPauseMenu(){
    PauseMenu* pauseMenu = new PauseMenu( gRenderer );
    pauseMenu->show();
    if(pauseMenu->accept() == MENU_QUIT)
        return false;
    return true;
}

// renderLose
void DisplaySystem::renderLose(){
    // // In renderLose function, we just need to render the lose text
    // gLoseTextTexture->render( LOSE_TEXTURE_POSITION_X - gLoseTextTexture->getWidth() / 2.0,
    //                          LOSE_TEXTURE_POSITION_Y - gLoseTextTexture->getHeight() / 2.0,
    //                          gRenderer );
    // //Update screen of our specified window
    // ResourceManager* RM = ResourceManager::getInstance();

    // SDL_GL_SwapWindow(getSDLWindow());
    // Mix_PlayChannel(-1, RM->getChunkResource("sound_gameover"), 0);
    // // When game lose, wait for 1 s
    // SDL_Delay( 1000 );
}

// renderWin
void DisplaySystem::renderWin(){
    // // In renderWin function, we just need to render the win text
    // gWinTextTexture->render( WIN_TEXTURE_POSITION_X - gWinTextTexture->getWidth() / 2.0,
    //                         WIN_TEXTURE_POSITION_Y - gWinTextTexture->getHeight() / 2.0,
    //                         gRenderer );
    // //Update screen of our specified window
    // SDL_GL_SwapWindow(getSDLWindow());
    // // When game wins, wait for 1 s
    // SDL_Delay( 1000 );
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


