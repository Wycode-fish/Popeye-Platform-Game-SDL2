#include "../include/mainmenu.h"

bool MainMenu::loadMedia(){
    // Load MainMenu
    bool success = true;
    // The MainMenu text
    std::stringstream mainMenuText;
    // The Start Menu text
    std::stringstream startText;
    // The Exit Menu text
    std::stringstream quitText;
    // The Language Setting text
    std::stringstream SettingText;
    // The Instrutction text
    std::stringstream instructionText;

    LTexture* gMainMenuTextTexture = new LTexture();

    LTexture* gStartTextTexture = new LTexture();

    LTexture* gQuitTextTexture = new LTexture();

    LTexture* gSettingTextTexture = new LTexture();

    LTexture* gInstructionTextTexture = new LTexture();

    // Set Quit text to be rendered
    quitText.str( "" );
    quitText << ResourceManager::getInstance()->getCurrentLanguageMap()["quit"];
    if ( !gQuitTextTexture->loadFromRenderedText( quitText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Quit Text Texture!\n";
    } else {
        labels[ "quit_text" ] = gQuitTextTexture;
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

    // Set start text to be rendered
    startText.str( "" );
    startText << ResourceManager::getInstance()->getCurrentLanguageMap()["press2start"];
    if ( !gStartTextTexture->loadFromRenderedText( startText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Start Text Texture!\n";
    } else {
        labels[ "start_text" ] = gStartTextTexture;
    }


    // Set main menu text to be rendered
    mainMenuText.str( "" );
    mainMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["mainMenu"];
    if ( !gMainMenuTextTexture->loadFromRenderedText( mainMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Main Menu Text Texture!\n";
    } else {
        labels[ "main_text" ] = gMainMenuTextTexture;
    }


    gMainMenuButtonSpriteSheet = ResourceManager::getInstance()->getTextureResource( "texture_main_menu_button_sprite_sheet" );
    if ( !gMainMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Main Menu Button Sprite Sheet!\n";
    }

    return success;
}

void MainMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;

    while (running){

        while (SDL_PollEvent( &event ) != 0){
            buttons[ "start_button" ]->handleEvent( &event );
            buttons[ "language_setting_button" ]->handleEvent( &event );
            buttons[ "quit_button" ]->handleEvent( &event );
            buttons[ "instruction_button" ]->handleEvent( &event );

            if ( buttons[ "start_button" ]->isClick() ){ // Start Button has been clicked
                running = false;
                break;
            } else if ( buttons[ "language_setting_button" ]->isClick() ){ // Language Setting Button has been clicked
                SettingMenu* settingMenu = new SettingMenu( gRenderer ); //  show and render languageSettingMenu
                settingMenu->show();
                loadMedia(); // When language changes, refresh the text
                break;
            } else if ( buttons[ "quit_button" ]->isClick() ){ //  Quit Button has been clicked
                running = false;
                message = MENU_QUIT;
                break;
            } else if ( buttons[ "instruction_button" ]->isClick() ){
                InstructionMenu* insturctionMenu = new InstructionMenu( gRenderer ); // show and render InstructionMenu
                insturctionMenu->show();
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

void MainMenu::render(){
    SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
    SDL_RenderClear(gRenderer);

    renderBackGround();

    renderButtons();

    renderLabels();



    SDL_RenderPresent( gRenderer );
}

void MainMenu::renderBackGround(){
    LTexture* gHeroTexture = ResourceManager::getInstance()->getTextureResource("texture_hero");
    LTexture* gBackGroundTexture = ResourceManager::getInstance()->getTextureResource("texture_map_kungfu");
    SDL_Rect clip;
    clip.x = 750.0f;
    clip.y = 0.0f;
    clip.w = WINDOW_WIDTH;
    clip.h = WINDOW_HEIGHT;
    gBackGroundTexture->render(0.0f, 0.0f,
                               gRenderer,
                               &clip);

    SDL_Rect hClip;
    hClip.x = 150.0f;
    hClip.y = 400.0f;
    hClip.w = 75.0f;
    hClip.h = 80.0f;
    SDL_Rect hShrink;
    hShrink.x = 0.0f;
    hShrink.y = 0.0f;
    hShrink.w = HERO_WIDTH_INITIAL * 2.0f;
    hShrink.h = HERO_HEIGHT_INITIAL * 2.0f;
    gHeroTexture->render(HERO_BACKGROUND_POSITION_X,
                         HERO_BACKGROUND_POSITION_Y,
                         gRenderer,
                         &hClip,
                         &hShrink);
}

void MainMenu::renderButtons(){

    for (std::map<std::string, LButton*>::iterator it = buttons.begin();
         it != buttons.end();
         it++){
        LButton* renderButton = it->second;
        renderButton->render( gMainMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
    }
}

void MainMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["main_text"];
    renderLabel->render( MAIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         MAIN_MENU_TEXTURE_POSITION_Y + labelNum * MAIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["start_text"];
    renderLabel->render( MAIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         MAIN_MENU_TEXTURE_POSITION_Y + labelNum * MAIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["setting_text"];
    renderLabel->render( MAIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         MAIN_MENU_TEXTURE_POSITION_Y + labelNum * MAIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;


    renderLabel = labels["instruction_text"];
    renderLabel->render( MAIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         MAIN_MENU_TEXTURE_POSITION_Y + labelNum * MAIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

    labelNum++;

    renderLabel = labels["quit_text"];
    renderLabel->render( MAIN_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         MAIN_MENU_TEXTURE_POSITION_Y + labelNum * MAIN_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer );

}

MENU_MESSAGE MainMenu::accept(){
    return message;
}

// Default destructor
MainMenu::~MainMenu(){
    // Now do nothing
    destroy();
}

void MainMenu::destroy(){

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

bool MainMenu::init( SDL_Renderer* gRenderer ){

    bool success = true;
    // Init map

    // Quit Button
    LButton* quitButton = new LButton();
    quitButton->setPosition( MAIN_MENU_QUIT_BUTTON_POSITION_X,
                             MAIN_MENU_QUIT_BUTTON_POSITION_Y);
    buttons[ "quit_button" ] = quitButton;

    // Instruction Button
    LButton* instructionButton = new LButton();
    instructionButton->setPosition( MAIN_MENU_INSTRUCTION_BUTTON_POSITION_X,
                                    MAIN_MENU_INSTRUCTION_BUTTON_POSITION_Y);
    buttons[ "instruction_button" ] = instructionButton;

    // Language Setting Button
    LButton* languageSettingButton = new LButton();
    languageSettingButton->setPosition( MAIN_MENU_LANGUAGE_SETTING_BUTTON_POSITION_X,
                                       MAIN_MENU_LANGUAGE_SETTING_BUTTON_POSITION_Y );
    buttons[ "language_setting_button" ] = languageSettingButton;

    // Start Button
    LButton* startButton = new LButton();
    startButton->setPosition( MAIN_MENU_START_BUTTON_POSITION_X, MAIN_MENU_START_BUTTON_POSITION_Y );
    buttons[ "start_button" ] = startButton;


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

MainMenu::MainMenu(){
    // Do Nothing
}

// Default constructor
MainMenu::MainMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init MainMenu!\n";

    if (!loadMedia()){
        cout << "Cannot Load MainMenu!\n";
    }
}
