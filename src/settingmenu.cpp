#include "../include/settingmenu.h"

bool SettingMenu::loadMedia(){
    // Load LS Menu
    bool success = true;
    // The LSMenu text
    std::stringstream SettingMenuText;
    // The First Language text
    std::stringstream FirstLText;
    // The Second Language text
    std::stringstream SecondLText;
    // The Return text
    std::stringstream ReturnText;

    LTexture* gSettingMenuTextTexture = new LTexture();

    LTexture* gFirstLTextTexture = new LTexture();

    LTexture* gSecondLTextTexture = new LTexture();

    LTexture* gReturnTextTexture = new LTexture();

    // Set setting menu text to be rendered
    SettingMenuText.str( "" );
    SettingMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["setting"];
    if ( !gSettingMenuTextTexture->loadFromRenderedText( SettingMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Setting Menu Text Texture!\n";
    } else {
        labels[ "setting_text" ] = gSettingMenuTextTexture;
    }

    // Set frist language text to be rendered
    FirstLText.str( "" );
    FirstLText << ResourceManager::getInstance()->getCurrentLanguageMap()["english"];
    if ( !gFirstLTextTexture->loadFromRenderedText( FirstLText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load First Language Text Texture!\n";
    } else {
        labels[ "first_text" ] = gFirstLTextTexture;
    }

    // Set second language text to be rendered
    SecondLText.str( "" );
    SecondLText << ResourceManager::getInstance()->getCurrentLanguageMap()["chinese"];
    if ( !gSecondLTextTexture->loadFromRenderedText( SecondLText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Second Language Text Texture!\n";
    } else {
        labels[ "second_text" ] = gSecondLTextTexture;
    }

    // Set Return Setting to be rendered
    ReturnText.str( "" );
    ReturnText << ResourceManager::getInstance()->getCurrentLanguageMap()["return"];
    if ( !gReturnTextTexture->loadFromRenderedText( ReturnText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Return Text Texture!\n";
    } else {
        labels[ "return_text" ] = gReturnTextTexture;
    }

    gSettingMenuButtonSpriteSheet = ResourceManager::getInstance()->getTextureResource( "texture_setting_menu_button_sprite_sheet" );
    if ( !gSettingMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Setting Menu Button Sprite Sheet!\n";
    }

    return success;
}

void SettingMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;

    while (running){

        while (SDL_PollEvent( &event ) != 0){
            buttons[ "first_language_button" ]->handleEvent( &event );
            buttons[ "second_language_button" ]->handleEvent( &event );
            buttons[ "return_button" ]->handleEvent( &event );

            if ( buttons[ "first_language_button" ]->isClick() ){ // First Language Button has been clicked
                if (ResourceManager::getInstance()->getCurrentLanguageMap()["life"] != "Life"){
                    ResourceManager::getInstance()->setCurrentLanguageMap("english");
                    loadMedia();// When language changes, refresh the text
                }
                break;
            } else if ( buttons[ "second_language_button" ]->isClick() ){ // Second Language Button has been clicked
                if (ResourceManager::getInstance()->getCurrentLanguageMap()["life"] == "Life"){
                    ResourceManager::getInstance()->setCurrentLanguageMap("chinese");
                    loadMedia();
                }
                break;
            } else if ( buttons[ "return_button" ]->isClick() ){ //  Quit Button has been clicked
                running = false;
                break;
            }
        }
        render();
    }
}

void SettingMenu::render(){
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    renderButtons();

    renderLabels();


    SDL_RenderPresent( gRenderer );
}

void SettingMenu::renderButtons(){
    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* renderButton = it->second;
        renderButton->render( gSettingMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
    }
}

void SettingMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["setting_text"];
    renderLabel->render( SETTING_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         SETTING_MENU_TEXTURE_POSITION_Y + labelNum * SETTING_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["first_text"];
    renderLabel->render( SETTING_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         SETTING_MENU_TEXTURE_POSITION_Y + labelNum * SETTING_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["second_text"];
    renderLabel->render( SETTING_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         SETTING_MENU_TEXTURE_POSITION_Y + labelNum * SETTING_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["return_text"];
    renderLabel->render( SETTING_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         SETTING_MENU_TEXTURE_POSITION_Y + labelNum * SETTING_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);


}

MENU_MESSAGE SettingMenu::accept(){
    return message;
}

// Default destructor
SettingMenu::~SettingMenu(){
    // Now do nothing
    destroy();
}

void SettingMenu::destroy(){

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

bool SettingMenu::init( SDL_Renderer* gRenderer ){
    bool success = true;
    // Init map
    // First Language Button
    LButton* firstLanguageButton = new LButton();
    firstLanguageButton->setPosition( SETTING_MENU_FIRST_LANGUAGE_BUTTON_POSITION_X,
                                     SETTING_MENU_FIRST_LANGUAGE_BUTTON_POSITION_Y );
    buttons[ "first_language_button" ] = firstLanguageButton;
    // Second Language Button
    LButton* secondLanguageButton = new LButton();
    secondLanguageButton->setPosition( SETTING_MENU_SECOND_LANGUAGE_BUTTON_POSITION_X,
                                       SETTING_MENU_SECOND_LANGUAGE_BUTTON_POSITION_Y );
    buttons[ "second_language_button" ] = secondLanguageButton;

    // Return Button
    LButton* returnButton = new LButton();
    returnButton->setPosition( SETTING_MENU_RETURN_BUTTON_POSITION_X,
                              SETTING_MENU_RETURN_BUTTON_POSITION_Y );
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

SettingMenu::SettingMenu(){
    // Do Nothing
}

// Default constructor
SettingMenu::SettingMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init MainMenu!\n";

    if (!loadMedia()){
        cout << "Cannot Load MainMenu!\n";
    }
}
