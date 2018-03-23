#include "../include/pausemenu.h"

bool PauseMenu::loadMedia(){
    // Load PauseMenu
    bool success = true;
    // The MainMenu text
    std::stringstream PauseMenuText;
    // The pasue/resume text
    std::stringstream resumeText;

    LTexture* gPauseMenuTextTexture = new LTexture();

    LTexture* gResumeTextTexture = new LTexture();

    // Set PauseMenuText text to be rendered
    PauseMenuText.str( "" );
    PauseMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["gamePause"];
    if ( !gPauseMenuTextTexture->loadFromRenderedText( PauseMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Pause Menu Text Texture!\n";
    } else {
        labels[ "pause_text" ] = gPauseMenuTextTexture;
    }

    // Set Resume Text to be rendered
    resumeText.str( "" );
    resumeText << ResourceManager::getInstance()->getCurrentLanguageMap()["press2resume"];
    if ( !gResumeTextTexture->loadFromRenderedText( resumeText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Resume Text Texture!\n";
    } else {
        labels[ "resume_text" ] = gResumeTextTexture;
    }

    gPauseMenuButtonSpriteSheet = NULL;

    return success;
}

void PauseMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;

    int countFrame = 0;

    while (running){


        while (SDL_PollEvent( &event ) != 0){

            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_q){
                    running = false;
                    message = MENU_QUIT;
                    break;
                } else if (event.key.keysym.sym == SDLK_SPACE){
                    cout << "PAUSE MENU SPACE DOWN!\n";
                    running = false;
                    return;
                } else {

                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
        SDL_RenderClear(gRenderer);

        renderLabels();

        SDL_RenderPresent( gRenderer );

        countFrame++;
    }
}

void PauseMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["pause_text"];
    renderLabel->render( PAUSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         PAUSE_MENU_TEXTURE_POSITION_Y + labelNum * PAUSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["resume_text"];
    renderLabel->render( PAUSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         PAUSE_MENU_TEXTURE_POSITION_Y + labelNum * PAUSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

}

MENU_MESSAGE PauseMenu::accept(){
    return message;
}

// Default destructor
PauseMenu::~PauseMenu(){
    // Now do nothing
    destroy();
}

void PauseMenu::destroy(){

    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* button = it->second;
        delete[] button;
    }

    for (std::map<std::string, LTexture*>::iterator it = labels.begin();
         it != labels.end();
         it++){
        LTexture* label = it->second;
        label->free();
        delete[] label;
    }

}

bool PauseMenu::init( SDL_Renderer* gRenderer ){

    bool success = true;
    // Init map

//    // Quit Button
//    LButton* quitButton = new LButton();
//    quitButton->setPosition( MAIN_MENU_QUIT_BUTTON_POSITION_X,
//                             MAIN_MENU_QUIT_BUTTON_POSITION_Y);
//    buttons[ "quit_button" ] = quitButton;

//    // Instruction Button
//    LButton* instructionButton = new LButton();
//    instructionButton->setPosition( MAIN_MENU_INSTRUCTION_BUTTON_POSITION_X,
//                                    MAIN_MENU_INSTRUCTION_BUTTON_POSITION_Y);
//    buttons[ "instruction_button" ] = instructionButton;

//    // Language Setting Button
//    LButton* languageSettingButton = new LButton();
//    languageSettingButton->setPosition( MAIN_MENU_LANGUAGE_SETTING_BUTTON_POSITION_X,
//                                       MAIN_MENU_LANGUAGE_SETTING_BUTTON_POSITION_Y );
//    buttons[ "language_setting_button" ] = languageSettingButton;

//    // Start Button
//    LButton* startButton = new LButton();
//    startButton->setPosition( MAIN_MENU_START_BUTTON_POSITION_X, MAIN_MENU_START_BUTTON_POSITION_Y );
//    buttons[ "start_button" ] = startButton;


//    // Init Sprite position (clip)
////    BUTTON_SPRITE_MOUSE_OUT = 0,
////    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
////    BUTTON_SPRITE_MOUSE_DOWN = 2,
////    BUTTON_SPRITE_MOUSE_UP = 3,
////    BUTTON_SPRITE_TOTAL = 4
//    //Set sprites
//    // When mouse out
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].x = 0;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].y = 49;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].w = 190;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].h = 45;

//    // When mouse hover
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].x = 0;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].y = 94;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].w = 190;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].h = 49;

//    // When mouse down
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].x = 190;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].y = 49;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].w = 190;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].h = 45;

//    // When mouse up
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].x = 0;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].y = 0;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].w = 190;
//    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].h = 49;

    // Init gRenderer in MainMenu
    this->gRenderer = gRenderer;

    if (this->gRenderer == NULL){
        cout << "Unable to init gRenderer in Main Menu!\n";
        success = false;
    }

    // Init gFont in MainMenu

    gFont = ResourceManager::getInstance()->getTureTypeFontResource("font_main");

    if (gFont == NULL){
        cout << "Unable to init gFont in Main Menu!\n";
        success = false;
    }

    return success;
}

PauseMenu::PauseMenu(){
    // Do Nothing
}

// Default constructor
PauseMenu::PauseMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init MainMenu!\n";

    if (!loadMedia()){
        cout << "Cannot Load MainMenu!\n";
    }
}
