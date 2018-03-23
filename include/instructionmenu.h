#ifndef INSTRUCTIONMENU_H
#define INSTRUCTIONMENU_H

#include "lbutton.h"
#include "ltexture.h"
#include "constants.h"
#include "resourcemanager.h"
#include "menu.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>

/**
 * @brief This class defines the instruction menu.
 *
 */
class InstructionMenu : public Menu{
public:

    InstructionMenu();

    InstructionMenu( SDL_Renderer* gRenderer );

    ~InstructionMenu();

    virtual bool loadMedia();

    virtual MENU_MESSAGE accept();

    virtual void show();

    virtual void destroy();

    bool init( SDL_Renderer* gRenderer );

    void renderLabels();

private:

    /** the map from name to LButton */
    std::map<std::string, LButton*> buttons;

    /** the map from name to Label */
    std::map<std::string, LTexture*> labels;

    /** Button Sprite Sheet */
    LTexture* gInstructionMenuButtonSpriteSheet = new LTexture();

    /** Mouse button sprites */
    SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
    // the SDL_Renderer
    SDL_Renderer* gRenderer = NULL;
    // MainMenu used font
    TTF_Font* gFont = NULL;
    // the text color, set to be white
    SDL_Color textColor = { 255, 255, 255, 255 };
    MENU_MESSAGE message;
};


#endif // INSTRUCTIONMENU_H
