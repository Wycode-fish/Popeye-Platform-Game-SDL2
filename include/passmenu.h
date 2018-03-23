#ifndef PASSMENU_H
#define PASSMENU_H


#include "lbutton.h"
#include "ltexture.h"
#include "constants.h"
#include "resourcemanager.h"
#include "menu.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>

/**
 * @brief This class defines the Pass menu.
 *
 */
class PassMenu : public Menu{
public:

    PassMenu();

    PassMenu( SDL_Renderer* gRenderer );

    ~PassMenu();

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
    LTexture* gPassMenuButtonSpriteSheet = new LTexture();

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


#endif // PASSMENU_H
