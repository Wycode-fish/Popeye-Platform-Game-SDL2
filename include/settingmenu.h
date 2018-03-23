#ifndef SETTINGMENU_H
#define SETTINGMENU_H


#include "lbutton.h"
#include "ltexture.h"
#include "constants.h"
#include "resourcemanager.h"
#include "menu.h"
#include <iostream>
#include <sstream>
#include <string>
#include <map>

/**
 * @brief This class defines the setting menu.
 *
 */
class SettingMenu : public Menu{
public:

    SettingMenu();

    SettingMenu( SDL_Renderer* gRenderer );

    ~SettingMenu();

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
    LTexture* gSettingMenuButtonSpriteSheet = new LTexture();

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


#endif // SETTINGMENU_H
