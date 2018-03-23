#include "../include/instructionmenu.h"

bool InstructionMenu::loadMedia(){
    // Load Instruction Menu
    bool success = true;

    std::stringstream InstructionMenuText;
    // The operation text
    std::stringstream OperationText;
    // The Pause \ Resume text
    std::stringstream PauseResumeText;
    // The Quit text
    std::stringstream QuitText;
    // The Return instruction text
    std::stringstream ReturnInsText;
    // The Return text
    std::stringstream ReturnText;

    LTexture* gInstructionMenuTextTexture = new LTexture();

    LTexture* gOperationTextTexture = new LTexture();

    LTexture* gPauseResumeTextTexture = new LTexture();

    LTexture* gQuitTextTexture = new LTexture();

    LTexture* gReturnInsTextTexture = new LTexture();

    LTexture* gReturnTextTexture = new LTexture();

    // Set instruction menu text to be rendered
    InstructionMenuText.str( "" );
    InstructionMenuText << ResourceManager::getInstance()->getCurrentLanguageMap()["instruction"];
    if ( !gInstructionMenuTextTexture->loadFromRenderedText( InstructionMenuText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Instruction Menu Text Texture!\n";
    } else {
        labels[ "instruction_text" ] = gInstructionMenuTextTexture;
    }

    // Set Operation text to be rendered
    OperationText.str( "" );
    OperationText << ResourceManager::getInstance()->getCurrentLanguageMap()["operation"];
    if ( !gOperationTextTexture->loadFromRenderedText( OperationText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Operation Text Texture!\n";
    } else {
        labels[ "operation_text" ] = gOperationTextTexture;
    }

    // Set pause/resume language text to be rendered
    PauseResumeText.str( "" );
    PauseResumeText << ResourceManager::getInstance()->getCurrentLanguageMap()["press2pause"];
    if ( !gPauseResumeTextTexture->loadFromRenderedText( PauseResumeText.str().c_str(), textColor, gFont, gRenderer ) ){
        success = false;
        std::cout << "Unable to load Pause/Resume Text Texture!\n";
    } else {
        labels[ "pause_resume_text" ] = gPauseResumeTextTexture;
    }

    // Set Quit Text to be rendered
    QuitText.str( "" );
    QuitText << ResourceManager::getInstance()->getCurrentLanguageMap()["press2quit"];
    if ( !gQuitTextTexture->loadFromRenderedText( QuitText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Instruction Quit Text Texture!\n";
    } else {
        labels[ "quit_text" ] = gQuitTextTexture;
    }

    // Set Return Instruction Text to be rendered
    ReturnInsText.str( "" );
    ReturnInsText << ResourceManager::getInstance()->getCurrentLanguageMap()["back2menu"];
    if ( !gReturnInsTextTexture->loadFromRenderedText( ReturnInsText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Return instruction Text Texture!\n";
    } else {
        labels[ "return_ins_text" ] = gReturnInsTextTexture;
    }

    // Set Return Text to be rendered
    ReturnText.str( "" );
    ReturnText << ResourceManager::getInstance()->getCurrentLanguageMap()["return"];
    if ( !gReturnTextTexture->loadFromRenderedText( ReturnText.str().c_str(), textColor, gFont, gRenderer )){
        success = false;
        std::cout << "Unable to load Return Text Texture!\n";
    } else {
        labels[ "return_text" ] = gReturnTextTexture;
    }


    gInstructionMenuButtonSpriteSheet = ResourceManager::getInstance()->getTextureResource( "texture_instruction_menu_button_sprite_sheet" );
    if ( !gInstructionMenuButtonSpriteSheet ){
        success = false;
        std::cout << "Unable to load Instruction Menu Button Sprite Sheet!\n";
    }

    return success;
}

void InstructionMenu::show(){
    // In this function, implement the complete logic for menu showing, like QT widget.
    SDL_Event event;

    bool running = true;

    while (running){

        while (SDL_PollEvent( &event ) != 0){
            buttons[ "return_button" ]->handleEvent( &event );

            if ( buttons[ "return_button" ]->isClick() ){ //  Quit Button has been clicked
                running = false;
                break;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0x22,0x22,0x22,0xFF);
        SDL_RenderClear(gRenderer);

        for (std::map<std::string, LButton*>::iterator it = buttons.begin();
             it != buttons.end();
             it++){
            LButton* renderButton = it->second;
            renderButton->render( gInstructionMenuButtonSpriteSheet, gRenderer, gSpriteClips[ renderButton->getCurrentSprite() ] );
        }

        renderLabels();

        SDL_RenderPresent( gRenderer );
    }
}

void InstructionMenu::renderLabels(){
    int labelNum = 0;

    LTexture* renderLabel = NULL;

    renderLabel = labels["instruction_text"];
    renderLabel->render( INSTRUCTION_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         INSTRUCTION_MENU_TEXTURE_POSITION_Y + labelNum * INSTRUCTION_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["operation_text"];
    renderLabel->render( INSTRUCTION_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         INSTRUCTION_MENU_TEXTURE_POSITION_Y + labelNum * INSTRUCTION_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["pause_resume_text"];
    renderLabel->render( INSTRUCTION_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         INSTRUCTION_MENU_TEXTURE_POSITION_Y + labelNum * INSTRUCTION_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["quit_text"];
    renderLabel->render( INSTRUCTION_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         INSTRUCTION_MENU_TEXTURE_POSITION_Y + labelNum * INSTRUCTION_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["return_ins_text"];
    renderLabel->render( INSTRUCTION_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         INSTRUCTION_MENU_TEXTURE_POSITION_Y + labelNum * INSTRUCTION_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

    labelNum++;
    renderLabel = labels["return_text"];
    renderLabel->render( INSTRUCTION_MENU_TEXTURE_POSITION_X - renderLabel->getWidth() / 2.0,
                         INSTRUCTION_MENU_TEXTURE_POSITION_Y + labelNum * INSTRUCTION_MENU_LABEL_SPACE - renderLabel->getHeight() / 2.0,
                         gRenderer);

}

MENU_MESSAGE InstructionMenu::accept(){
    return message;
}

// Default destructor
InstructionMenu::~InstructionMenu(){
    // Now do nothing
    destroy();
}

void InstructionMenu::destroy(){

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

bool InstructionMenu::init( SDL_Renderer* gRenderer ){

    // Init map
//    // First Language Button
//    LButton* firstLanguageButton = new LButton();
//    firstLanguageButton->setPosition( SETTING_MENU_FIRST_LANGUAGE_BUTTON_POSITION_X,
//                                     SETTING_MENU_FIRST_LANGUAGE_BUTTON_POSITION_Y );
//    buttons[ "first_language_button" ] = firstLanguageButton;
//    // Second Language Button
//    LButton* secondLanguageButton = new LButton();
//    secondLanguageButton->setPosition( SETTING_MENU_SECOND_LANGUAGE_BUTTON_POSITION_X,
//                                       SETTING_MENU_SECOND_LANGUAGE_BUTTON_POSITION_Y );
//    buttons[ "second_language_button" ] = secondLanguageButton;

    // Return Button
    bool success = true;
    LButton* returnButton = new LButton();
    returnButton->setPosition( INSTRUCTION_MENU_RETURN_BUTTON_POSITION_X,
                              INSTRUCTION_MENU_RETURN_BUTTON_POSITION_Y );
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

InstructionMenu::InstructionMenu(){
    // Do Nothing
}

// Default constructor
InstructionMenu::InstructionMenu( SDL_Renderer* gRenderer ){

    if(!init( gRenderer ))
        cout << "Cannot Init Instruction Menu!\n";

    if (!loadMedia()){
        cout << "Cannot Load Instruction Menu!\n";
    }
}
