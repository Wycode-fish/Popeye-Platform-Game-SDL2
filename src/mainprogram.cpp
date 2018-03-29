#include "../include/mainprogram.h"

MainProgram* MainProgram::gMainProgram = NULL;

MainProgram* MainProgram::getInstance(){
    if ( !gMainProgram )
        gMainProgram = new MainProgram();
    return gMainProgram;
}

MainProgram::MainProgram(){

}

MainProgram::~MainProgram(){

}

void MainProgram::run(){
    if (init()){
//        Mix_PlayMusic( ResourceManager::getInstance()->getMixMusicResource("music_background"), -1 );
        loop();
    } else {
        cout << "Main Program Init Failure!\n";
    }
}

void MainProgram::loop(){

    /******     Timer Initialization      *****/
    //The frames per second timer
    LTimer fpsTimer;
    //The frames per second cap timer
    LTimer capTimer;
    //Start counting frames per second
    int countedFrames = 0;
    fpsTimer.start();


    /******     Systems Initialization      *****/
    bool quit = false;
    bool running = true;
    SDL_Event event;



    //While application is running
    while( running )
    {
        if (countedFrames == 0){
            GameSetting::getInstance()->reset();
            SoundSystem::getInstance()->playMainMenuBackground();
            switch (DisplaySystem::getInstance()->renderMainMenu()) {
            case MENU_QUIT:{
                running = false;
                break;
            }
            default:{
                SoundSystem::getInstance()->start();
                break;
            }
            }
        }
        // FPS capping
        capTimer.start();
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 ) avgFPS = 0;


        /******     Component Systems update      *****/
        while( SDL_PollEvent( &event ) != 0 ){
            switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_q){
                    running = false;
                    break;
                }
                else if (event.key.keysym.sym == SDLK_SPACE){
                    //SDL_PollEvent( &event );
                    cout << "Main Program space key down!\n";
                    switch (DisplaySystem::getInstance()->renderPauseMenu()) {
                    case MENU_QUIT:{
                        running = false;
                        break;
                    }
                    case MENU_RETURN:{
                        countedFrames = -1;
                        break;
                    }
                    default:
                        break;
                    }
                } else if (event.key.keysym.sym == SDLK_ESCAPE){
                    countedFrames = -1;
                }
                else ControlSystem::getInstance()->update(event);
                break;
            default:
                ControlSystem::getInstance()->update(event);
            }
        }

        if (countedFrames == -1){
            countedFrames++;
            continue;
        }

        CollisionSystem::getInstance()->update();
        cout << "CollisionSystem update!\n";

        PlaySystem::getInstance()->update();
        cout << "PlaySystem update!\n";

        Camera::getInstance()->update();
        cout << "Camera Pos update!\n";

        DisplaySystem::getInstance()->update();
        cout << "DisplaySystem update!\n";

        SoundSystem::getInstance()->update();
        cout << "SoundSystem update!\n";

        /******     Win/Lose Check      *****/
        if (PlaySystem::getInstance()->isLose()) {
//            GameSetting::getInstance()->init();
//            PlaySystem::getInstance()->reset();
            SoundSystem::getInstance()->pauseCurrentLevelBackground();
            SoundSystem::getInstance()->playLoseSound();
            switch (DisplaySystem::getInstance()->renderLoseMenu()) {
            case MENU_QUIT:{
                running = false;
                break;
            }
            case MENU_RETURN:{
                countedFrames = -1;
                PlaySystem::getInstance()->reset();
                break;
            }
            default:{
                GameSetting::getInstance()->initCurrentLevel();
                PlaySystem::getInstance()->reset();
                SoundSystem::getInstance()->resumeCurrentLevelBackground();
                break;
            }
            }
        }
        if ( PlaySystem::getInstance()->isWin() ){
//            GameSetting::getInstance()->init();
            SoundSystem::getInstance()->pauseCurrentLevelBackground();
            SoundSystem::getInstance()->playWinSound();
            PlaySystem::getInstance()->reset();
            switch (DisplaySystem::getInstance()->renderWinMenu()) {
            case MENU_RETURN:{
                countedFrames = -1;
                break;
            }
            case MENU_QUIT:{
                running = false;
                break;
            }
            default:
                break;
            }
        }
        if ( PlaySystem::getInstance()->isHeroPass() ){
            SoundSystem::getInstance()->pauseCurrentLevelBackground();
            SoundSystem::getInstance()->playPassSound();
            switch (DisplaySystem::getInstance()->renderPassMenu()) {
            case MENU_QUIT:{
                running = false;
                break;
            }
            default:
                break;
            }
        }


        /******     FPS Control      *****/
        ++countedFrames;
        //If frame finished early
        int frameTicks = capTimer.getTicks();
        if( frameTicks < screenTickPerFrame )
        {
            //Wait remaining time
            SDL_Delay( screenTickPerFrame - frameTicks );
        }
    }
}

bool MainProgram::init(){


    /******     Component Systems Initialization      *****/
    bool rm = ResourceManager::getInstance()->init();
    if (!rm){
        cout << "ResourceManager init failed!\n";
        return -1;
    }
    bool gs = GameSetting::getInstance()->init();
    if (!gs){
        cout << "GameSetting init failed!\n";
        return -1;
    }
    bool cs = ControlSystem::getInstance()->init();
    if (!cs){
        cout << "ControlSystem init failed!\n";
        return -1;
    }

    bool cos = CollisionSystem::getInstance()->init();
    if (!cos){
        cout << "CollisionSystem init failed!\n";
        return -1;
    }
    bool ds = DisplaySystem::getInstance()->init();
    if (!ds){
        cout << "DisplaySystem init failed!\n";
        return -1;
    }
    bool ps = PlaySystem::getInstance()->init();
    if (!ps){
        cout << "PlaySystem init failed!\n";
        return -1;
    }

    bool ss = SoundSystem::getInstance()->init();
    if (!ss){
        cout << "SoundSystem init failed!\n";
        return -1;
    }

    return rm && gs && cs && ps && cos && ds && ss;
}
