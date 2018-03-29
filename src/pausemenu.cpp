#include "../include/pausemenu.h"

bool PauseMenu::loadMedia(){
    // Load PauseMenu
    bool success = true;
    // The MainMenu text
    std::stringstream PauseMenuText;
    // The pasue/resume text
    std::stringstream resumeText;
    // The Language Setting text
    std::stringstream SettingText;
    // The Instrutction text
    std::stringstream instructionText;
    // The Return text
    std::stringstream ReturnText;

    LTexture* gPauseMenuTextTexture = new LTexture();

    LTexture* gResumeTextTexture = new LTexture();

    LTexture* gSettingTextTexture = new LTexture();

    LTexture* gInstructionTextTexture = new LTexture();

    LTexture* gReturnTextTexture = new LTexture();


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

    // Set Instruction Text to be rendered
    instructionText.str( "" );
    instructionText << ResourceManager::getInstance()->getCurrentLanguageMap()["instruction"];
    if ( !gInstructionTextTexture->loadFromRenderedText( instructionText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Instruction Text Texture!\n";
    } else {
        labels[ "instruction_text" ] = gInstructionTextTexture;
    }

    // Set Setting to be rendered
    SettingText.str( "" );
    SettingText << ResourceManager::getInstance()->getCurrentLanguageMap()["setting"];
    if ( !gSettingTextTexture->loadFromRenderedText( SettingText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Setting Text Texture!\n";
    } else {
        labels[ "setting_text" ] = gSettingTextTexture;
    }

    // Set Return Text to be rendered
    ReturnText.str( "" );
    ReturnText << ResourceManager::getInstance()->getCurrentLanguageMap()["return2menu"];
    if ( !gReturnTextTexture->loadFromRenderedText( ReturnText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Return Text Texture!\n";
    } else {
        labels[ "return_text" ] = gReturnTextTexture;
    }


    gPauseMenuButtonSpriteSheet = ResourceManager::getInstance()->getTextureResource( "texture_pause_menu_button_sprite_sheet" );
    if ( !gPauseMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Pause Menu Button Sprite Sheet!\n";
    };

    return success;
}

void PauseMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;

    while (running){


        while (SDL_PollEvent( &event ) != 0){

            buttons["setting_button"]->handleEvent(&event);

            buttons["instruction_button"]->handleEvent(&event);

            buttons["return_button"]->handleEvent(&event);

            if (buttons["setting_button"]->isClick()){
                SettingMenu* settingMenu = new SettingMenu( gRenderer );
                settingMenu->show();
                loadMedia();
                break;
            }

            if (buttons["instruction_button"]->isClick()){
                InstructionMenu* instructionMenu = new InstructionMenu( gRenderer );
                instructionMenu->show();
                break;
            }

            if (buttons["return_button"]->isClick()){
                message = MENU_RETURN;
                running = false;
                break;
            }

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

        render();

    }
}

void PauseMenu::render(){
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    renderButtons();

    renderLabels();

    SDL_RenderPresent( gRenderer );
}

void PauseMenu::renderButtons(){
    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* renderButton = it->second;
        renderButton->render( gPauseMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
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

    labelNum++;

    renderLabel = labels["setting_text"];
    renderLabel->render( PAUSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         PAUSE_MENU_TEXTURE_POSITION_Y + labelNum * PAUSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["instruction_text"];
    renderLabel->render( PAUSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         PAUSE_MENU_TEXTURE_POSITION_Y + labelNum * PAUSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["return_text"];
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

    // Setting Button
    LButton* settingButton = new LButton();
    settingButton->setPosition( PAUSE_MENU_SETTING_BUTTON_POSITION_X,
                             PAUSE_MENU_SETTING_BUTTON_POSITION_Y);
    buttons[ "setting_button" ] = settingButton;

    // Instruction Button
    LButton* instructionButton = new LButton();
    instructionButton->setPosition( PAUSE_MENU_INSTRUCTION_BUTTON_POSITION_X,
                                    PAUSE_MENU_INSTRUCTION_BUTTON_POSITION_Y);
    buttons[ "instruction_button" ] = instructionButton;

    // Return Button
    LButton* returnButton = new LButton();
    returnButton->setPosition( PAUSE_MENU_RETURN_BUTTON_POSITION_X,
                                    PAUSE_MENU_RETURN_BUTTON_POSITION_Y);
    buttons[ "return_button" ] = returnButton;




//    // Init Sprite position (clip)
////    BUTTON_SPRITE_MOUSE_OUT = 0,
////    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
////    BUTTON_SPRITE_MOUSE_DOWN = 2,
////    BUTTON_SPRITE_MOUSE_UP = 3,
////    BUTTON_SPRITE_TOTAL = 4
    //Set sprites
    // When mouse out
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].x = 0;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].y = 49;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].w = 190;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OUT ].h = 45;

    // When mouse hover
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].x = 0;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].y = 94;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].w = 190;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_OVER_MOTION ].h = 49;

    // When mouse down
    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].x = 190;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].y = 49;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].w = 190;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_DOWN ].h = 45;

    // When mouse up
    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].x = 0;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].y = 0;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].w = 190;
    gSpriteClips [ BUTTON_SPRITE_MOUSE_UP ].h = 49;

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
