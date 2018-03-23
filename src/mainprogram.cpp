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

string MainProgram::getCurrentWorkingDirectory(void)
{
    char path[1024];
    getcwd(path, sizeof(path));
    string str(path);
    return str;
}

void MainProgram::run(){
    if (init()){
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
            if ( !DisplaySystem::getInstance()->renderMainMenu() )
                running = false;
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
                    if ( !DisplaySystem::getInstance()->renderPauseMenu() ){
                        running = false;
                        break;
                    }
                } else if (event.key.keysym.sym == SDLK_ESCAPE){
                    countedFrames = -1;
                }
                else ControlSystem::getInstance()->update(event);
            }
        }

        CollisionSystem::getInstance()->update();
        cout << "CollisionSystem update!\n";

        PlaySystem::getInstance()->update();
        cout << "PlaySystem update!\n";

        Camera::getInstance()->update();
        cout << "Camera Pos update!\n";

        DisplaySystem::getInstance()->update();
        cout << "DisplaySystem update!\n";


        /******     Win/Lose Check      *****/
        if (PlaySystem::getInstance()->isLose()) {
            GameSetting::getInstance()->init();
            PlaySystem::getInstance()->reset();
        }
        if ( PlaySystem::getInstance()->isWin() ){
            PlaySystem::getInstance()->reset();
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

    /******     For TileMap Initialization      *****/
    string fileName = "";
    fileName = fileName + getCurrentWorkingDirectory() + "/" + "assets/maps/info/test2.txt";
    int groundIndexArray[] = {0, 2};
    vector<int> groundIndexSet (groundIndexArray, groundIndexArray + sizeof(groundIndexArray) / sizeof(int));
    TileMapSystem::getInstance()->onLoad( fileName, groundIndexSet, MAP_TYPE_NORMAL );


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
    bool ps = PlaySystem::getInstance()->init();
    if (!ps){
        cout << "PlaySystem init failed!\n";
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

    return rm && gs && cs && ps && cos && ds;
}
