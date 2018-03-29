#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "lbutton.h"
#include "ltexture.h"
#include "constants.h"
#include "resourcemanager.h"
#include "instructionmenu.h"
#include "settingmenu.h"
#include "menu.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>

/**
 * @brief This class defines the pause menu.
 *
 */
class PauseMenu : public Menu{
public:

    PauseMenu();

    PauseMenu( SDL_Renderer* gRenderer );

    ~PauseMenu();

    virtual bool loadMedia();

    virtual MENU_MESSAGE accept();

    virtual void show();

    virtual void destroy();

    virtual void render();

    bool init( SDL_Renderer* gRenderer );

    void renderButtons();

    void renderLabels();

private:

    /** the map from name to LButton */
    std::map<std::string, LButton*> buttons;

    /** the map from name to Label */
    std::map<std::string, LTexture*> labels;

    /** Button Sprite Sheet */
    LTexture* gPauseMenuButtonSpriteSheet = new LTexture();

    /** Mouse button sprites */
    SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];
    // the SDL_Renderer
    SDL_Renderer* gRenderer = NULL;
    // MainMenu used font
    TTF_Font* gFont = NULL;
    // the text color, set to be white
    SDL_Color textColor = { 255, 255, 255, 255 };

    MENU_MESSAGE message = MENU_NONE;// To get the message from menu whether the program is over
};

#endif // PAUSEMENU_H
