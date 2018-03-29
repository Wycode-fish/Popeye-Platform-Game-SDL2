
//  DisplaySystem.h
//  BreakoutGame-TX
//
//  Created by Tianxiang Dai on 2/18/18.
//  Copyright © 2018 Tianxiang Dai. All rights reserved.
//

// This class sets the displaysystem
// Singleton Design Pattern

#ifndef DisplaySystem_h
#define DisplaySystem_h

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "ltexture.h"
#include "playsystem.h"
#include "hero.h"
#include "collisionsystem.h"
#include "controlsystem.h"
#include "resourcemanager.h"
#include "passmenu.h"
#include "constants.h"
#include "system.h"
#include "camera.h"
#include "mainmenu.h"
#include "pausemenu.h"
#include "losemenu.h"
#include "winmenu.h"

#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

/**
 * @brief This class defines the display system.
 *
 * The display system creates game window, renders image for game objects, and
 * plays sound and music.
 */
class DisplaySystem: public System{
public:
    /**
     * @brief static instance function
     *
     * @return the only instance
     */
    static DisplaySystem* getInstance();
    /**
     * @brief Default destructor
     */
    ~DisplaySystem();
    /**
     * @brief Initialization
     *
     * @return true if succeeds
     */
    bool init();
    /**
     * @brief Quit the display system
     *
     * @return true if succeeds
     */
    bool quit();
    /**
     * @brief Load image/sound/music media
     *
     * @return true if succeeds
     */
    bool loadMedia();

    /**
     * @brief Render loaded textures
     */
    void render();
    /**
     * @brief render the lose scene
     */
    MENU_MESSAGE renderLoseMenu();
    /**
     * @brief render the win scene
     */
    MENU_MESSAGE renderWinMenu();
    /**
     * @brief render main menu on event
     */
    MENU_MESSAGE renderMainMenu();

    MENU_MESSAGE renderPauseMenu();

    MENU_MESSAGE renderPassMenu();

    /**
     * @brief Update the window at every frame
     */
    void update();

    void updateMapTexture();
    /**
     * @brief Get SDL_Window
     */
    SDL_Window* getSDLWindow();
    /**
     * @brief Get SDL_Renderer
     */
    SDL_Renderer* getSDLRenderer();

public:

    void renderHero();

    void renderView();

    void renderMinions();

    void renderBullets();

    void renderPowerUps();

    void renderInfo();

    bool loadInfoTexture();

    void renderCheckPoints();

    void renderCollectibles();


private:
    /**
     * @brief Private default constructor
     */
    DisplaySystem();

    static DisplaySystem* g_DisplaySystem; /**< the only instance */
    SDL_Window* gWindow = NULL; /**< the window we will be rendering to */
    SDL_Renderer* gRenderer = NULL; /**< SDL Renderer */

    LTexture* gLifeTextTexture = new LTexture(); /**< life texture */
    LTexture* gScoreTextTexture = new LTexture(); /**< score texture */
    LTexture* gLevelTextTexture = new LTexture(); /**< level texture */
    LTexture* gStateTextTexture = new LTexture(); /** Power Up State*/
    LTexture* gPowerUpIconTexture = new LTexture(); /**< PowerUp icon text texture */
    LTexture* gCheckPointTexture = new LTexture(); /** <CheckPoint texture>*/

    LTexture* gMapTexture = new LTexture();
    LTexture* gHeroTexture = new LTexture(); /**< ball texture */
    LTexture* gMinionTexture = new LTexture(); /**< brick texture */
    LTexture* gBulletTexture = new LTexture();
    LTexture* gPowerUpTexture = new LTexture();
    LTexture* gCollectibleTexture = new LTexture();



    TTF_Font* gFont = NULL; /**< globally used font */
    SDL_Color textColor = { 255, 255, 255, 255 }; /**< set the text color to white */

private:

    int mapWidth = MAP_WIDTH;

    int mapHeight = MAP_HEIGHT;

};

#endif

