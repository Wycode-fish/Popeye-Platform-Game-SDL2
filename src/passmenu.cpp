#include "../include/passmenu.h"

bool PassMenu::loadMedia(){
    // Load PassMenu
    bool success = true;
    // The PassMenu text
    std::stringstream passMenuText;
    // The next text
    std::stringstream nextText;

    LTexture* gPassMenuTextTexture = new LTexture();

    LTexture* gNextTextTexture = new LTexture();

    // Set PassMenuText text to be rendered
    passMenuText.str( "" );
    passMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["pass"];
    if ( !gPassMenuTextTexture->loadFromRenderedText( passMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Pass Menu Text Texture!\n";
    } else {
        labels[ "pass_text" ] = gPassMenuTextTexture;
    }

    // Set Next Text to be rendered
    nextText.str( "" );
    nextText << ResourceManager::getInstance()->getCurrentLanguageMap()["next"];
    if ( !gNextTextTexture->loadFromRenderedText( nextText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Next Text Texture!\n";
    } else {
        labels[ "next_text" ] = gNextTextTexture;
    }

    gPassMenuButtonSpriteSheet =  ResourceManager::getInstance()->getTextureResource( "texture_pass_menu_button_sprite_sheet" );
    if ( !gPassMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Pass Menu Button Sprite Sheet!\n";
    };

    return success;
}

void PassMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;


    while (running){


        while (SDL_PollEvent( &event ) != 0){
            buttons["next_button"]->handleEvent( &event );

            if ( buttons[ "next_button" ]->isClick() ){ // Next Button has been clicked
                running = false;
                break;
            }

            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_q){
                    running = false;
                    message = MENU_QUIT;
                    break;
                }
            }
        }
        render();
    }
}

void PassMenu::render(){
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    renderButtons();

    renderLabels();

    SDL_RenderPresent( gRenderer );
}


void PassMenu::renderButtons(){
    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* renderButton = it->second;
        renderButton->render( gPassMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
    }
}

void PassMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["pass_text"];
    renderLabel->render( PASS_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         PASS_MENU_TEXTURE_POSITION_Y + labelNum * PASS_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["next_text"];
    renderLabel->render( PASS_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         PASS_MENU_TEXTURE_POSITION_Y + labelNum * PASS_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

}

MENU_MESSAGE PassMenu::accept(){
    return message;
}

// Default destructor
PassMenu::~PassMenu(){
    // Now do nothing
    destroy();
}

void PassMenu::destroy(){

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

bool PassMenu::init( SDL_Renderer* gRenderer ){

    bool success = true;
     //Init map

    // Quit Button
    LButton* nextButton = new LButton();
    nextButton->setPosition( PASS_MENU_NEXT_BUTTON_POSITION_X,
                             PASS_MENU_NEXT_BUTTON_POSITION_Y);
    buttons[ "next_button" ] = nextButton;

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


    // Init Sprite position (clip)
//    BUTTON_SPRITE_MOUSE_OUT = 0,
//    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
//    BUTTON_SPRITE_MOUSE_DOWN = 2,
//    BUTTON_SPRITE_MOUSE_UP = 3,
//    BUTTON_SPRITE_TOTAL = 4
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

PassMenu::PassMenu(){
    // Do Nothing
}

// Default constructor
PassMenu::PassMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init MainMenu!\n";

    if (!loadMedia()){
        cout << "Cannot Load MainMenu!\n";
    }
}
