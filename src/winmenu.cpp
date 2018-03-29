#include "../include/winmenu.h"

bool WinMenu::loadMedia(){
    // Load Win Menu
    bool success = true;
    // The Win Menu text
    std::stringstream winMenuText;
    // The return text
    std::stringstream returnText;
    // The quit text
    std::stringstream quitText;

    LTexture* gWinMenuTextTexture = new LTexture();

    LTexture* gReturnTextTexture = new LTexture();

    LTexture* gQuitTextTexture = new LTexture();

    // Set WinMenuText text to be rendered
    winMenuText.str( "" );
    winMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["winMessage"];
    if ( !gWinMenuTextTexture->loadFromRenderedText( winMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Win Menu Text Texture!\n";
    } else {
        labels[ "win_text" ] = gWinMenuTextTexture;
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

    // Set Quit text to be rendered
    quitText.str( "" );
    quitText << ResourceManager::getInstance()->getCurrentLanguageMap()["quit"];
    if ( !gQuitTextTexture->loadFromRenderedText( quitText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Quit Text Texture!\n";
    } else {
        labels[ "quit_text" ] = gQuitTextTexture;
    }

    gWinMenuButtonSpriteSheet =  ResourceManager::getInstance()->getTextureResource( "texture_win_menu_button_sprite_sheet" );
    if ( !gWinMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Lose Menu Button Sprite Sheet!\n";
    };

    return success;
}

void WinMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;


    while (running){


        while (SDL_PollEvent( &event ) != 0){
            buttons["return_button"]->handleEvent( &event );

            buttons["quit_button"]->handleEvent( &event );

            if ( buttons[ "return_button" ]->isClick() ){ // Next Button has been clicked
                running = false;
                message = MENU_RETURN;
                break;
            }

            if ( buttons[ "quit_button" ]->isClick() ){
                running = false;
                message = MENU_QUIT;
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

void WinMenu::render(){
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    renderButtons();

    renderLabels();

    SDL_RenderPresent( gRenderer );
}


void WinMenu::renderButtons(){
    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* renderButton = it->second;
        renderButton->render( gWinMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
    }
}

void WinMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["win_text"];
    renderLabel->render( WIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         WIN_MENU_TEXTURE_POSITION_Y + labelNum * WIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["return_text"];
    renderLabel->render( WIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         WIN_MENU_TEXTURE_POSITION_Y + labelNum * WIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["quit_text"];
    renderLabel->render( WIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         WIN_MENU_TEXTURE_POSITION_Y + labelNum * WIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

}

MENU_MESSAGE WinMenu::accept(){
    return message;
}

// Default destructor
WinMenu::~WinMenu(){
    // Now do nothing
    destroy();
}

void WinMenu::destroy(){

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

bool WinMenu::init( SDL_Renderer* gRenderer ){

    bool success = true;
     //Init map

    // return Button
    LButton* returnButton = new LButton();
    returnButton->setPosition( WIN_MENU_RETURN_BUTTON_POSITION_X,
                               WIN_MENU_RETURN_BUTTON_POSITION_Y);
    buttons[ "return_button" ] = returnButton;

    // return Button
    LButton* quitButton = new LButton();
    quitButton->setPosition( WIN_MENU_QUIT_BUTTON_POSITION_X,
                             WIN_MENU_QUIT_BUTTON_POSITION_Y);
    buttons[ "quit_button" ] = quitButton;


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

WinMenu::WinMenu(){
    // Do Nothing
}

// Default constructor
WinMenu::WinMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init MainMenu!\n";

    if (!loadMedia()){
        cout << "Cannot Load MainMenu!\n";
    }
}
