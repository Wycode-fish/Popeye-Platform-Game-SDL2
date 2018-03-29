#include "../include/losemenu.h"

bool LoseMenu::loadMedia(){
    // Load LoseMenu
    bool success = true;
    // The LoseMenu text
    std::stringstream loseMenuText;
    // The restart text
    std::stringstream restartText;
    // The return text
    std::stringstream returnText;

    LTexture* gLoseMenuTextTexture = new LTexture();

    LTexture* gRestartTextTexture = new LTexture();

    LTexture* gReturnTextTexture = new LTexture();

    // Set LoseMenuText text to be rendered
    loseMenuText.str( "" );
    loseMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["loseMessage"];
    if ( !gLoseMenuTextTexture->loadFromRenderedText( loseMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Lose Menu Text Texture!\n";
    } else {
        labels[ "lose_text" ] = gLoseMenuTextTexture;
    }

    // Set Restart Text to be rendered
    restartText.str( "" );
    restartText << ResourceManager::getInstance()->getCurrentLanguageMap()["restart"];
    if ( !gRestartTextTexture->loadFromRenderedText( restartText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Restart Text Texture!\n";
    } else {
        labels[ "restart_text" ] = gRestartTextTexture;
    }

    // Set Return Text to be rendered
    returnText.str( "" );
    returnText << ResourceManager::getInstance()->getCurrentLanguageMap()["return"];
    if ( !gReturnTextTexture->loadFromRenderedText( returnText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Return Text Texture!\n";
    } else {
        labels[ "return_text" ] = gReturnTextTexture;
    }

    gLoseMenuButtonSpriteSheet =  ResourceManager::getInstance()->getTextureResource( "texture_lose_menu_button_sprite_sheet" );
    if ( !gLoseMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Lose Menu Button Sprite Sheet!\n";
    };

    return success;
}

void LoseMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;


    while (running){


        while (SDL_PollEvent( &event ) != 0){
            buttons["restart_button"]->handleEvent( &event );

            buttons["return_button"]->handleEvent( &event );

            if ( buttons[ "restart_button" ]->isClick() ){ // Next Button has been clicked
                running = false;
                break;
            }

            if ( buttons[ "return_button" ]->isClick() ){
                running = false;
                message = MENU_RETURN;
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

void LoseMenu::render(){
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    renderButtons();

    renderLabels();

    SDL_RenderPresent( gRenderer );
}


void LoseMenu::renderButtons(){
    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* renderButton = it->second;
        renderButton->render( gLoseMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
    }
}

void LoseMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["lose_text"];
    renderLabel->render( LOSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         LOSE_MENU_TEXTURE_POSITION_Y + labelNum * LOSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["restart_text"];
    renderLabel->render( LOSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         LOSE_MENU_TEXTURE_POSITION_Y + labelNum * LOSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["return_text"];
    renderLabel->render( LOSE_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         LOSE_MENU_TEXTURE_POSITION_Y + labelNum * LOSE_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

}

MENU_MESSAGE LoseMenu::accept(){
    return message;
}

// Default destructor
LoseMenu::~LoseMenu(){
    // Now do nothing
    destroy();
}

void LoseMenu::destroy(){

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

bool LoseMenu::init( SDL_Renderer* gRenderer ){

    bool success = true;
     //Init map

    // restart Button
    LButton* restartButton = new LButton();
    restartButton->setPosition( LOSE_MENU_RESTART_BUTTON_POSITION_X,
                             LOSE_MENU_RESTART_BUTTON_POSITION_Y);
    buttons[ "restart_button" ] = restartButton;

    // return Button
    LButton* returnButton = new LButton();
    returnButton->setPosition( LOSE_MENU_RETURN_BUTTON_POSITION_X,
                             LOSE_MENU_RETURN_BUTTON_POSITION_Y);
    buttons[ "return_button" ] = returnButton;


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

LoseMenu::LoseMenu(){
    // Do Nothing
}

// Default constructor
LoseMenu::LoseMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init MainMenu!\n";

    if (!loadMedia()){
        cout << "Cannot Load MainMenu!\n";
    }
}
