//
//  ResourceManager.h
//  BreakoutGame-TX
//
//  Created by Tianxiang Dai on 2/18/18.
//  Copyright © 2018 Tianxiang Dai. All rights reserved.
//

// This class represents the resourceManager in the game, including textures, videos and audios.
#ifndef ResourceManager_h
#define ResourceManager_h

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "constants.h"
#include "ltexture.h"
#include "system.h"
#include "tilemapsystem.h"
#include <unistd.h>
//#include <QApplication>


using namespace std;

/**
 * @brief This class defines the resource manager.
 *
 * A resource manager loads resources including textures, videos and audios from files.
 *
 * Applied Singleton Design Pattern
 */
class ResourceManager: public System{
public:
    /**
     * @brief Get the ResourceManager instance
     */
    static ResourceManager* getInstance();
    /**
     * @brief Default destructor
     */
    ~ResourceManager();
    /**
     * @brief Initialization
     */
    bool init();
    /**
     * @brief Initialization with a renderer
     */
    bool init( SDL_Renderer* gRenderer );
    /**
     * @brief Quit resource manager
     */
    bool quit();
    /**
     * @brief Update
     */
    void update();

    /**
     * Load LTexture resource
     *
     * @param  renderer the renderer to render texture resource
     * @param  path     the path of the resource
     * @return          a pointer to the texture
     */
    bool loadTextureResource( SDL_Renderer* renderer, const char* path, std::string key_name );
    /**
     * @brief Load Ture Type Font resource
     *
     * @param  renderer the renderer to render font resource
     * @param  path     the path of the resource
     * @param  size     the size of the resource
     * @return          a pointer to the font
     */
    bool loadTureTypeFontResource( SDL_Renderer* renderer, const char* path, int size, std::string key_name );
    /**
     * @brief Load Music resource
     *
     * @param  path the path of the resource
     * @return      a pointer to the music of type mix_music
     */
    bool loadMixMusicResource( const char* path, std::string key_name );
    /**
     * @brief Load Chunk resource
     *
     * @param  path the path of the resource
     * @return      a pointer to the sound of type mix_chunk
     */
    bool loadChunkResource( const char* path, std::string key_name );

    bool loadTileMapResource();

    /**
     * @brief Get the texture resource from a texture map
     *
     * @param key_name the key of the texture
     */
    LTexture* getTextureResource(std::string key_name);
    /**
     * @brief Get the font resource from a font map
     *
     * @param  key_name the key of the font
     */
    TTF_Font* getTureTypeFontResource(std::string key_name);
    /**
     * @brief Get the music resource from a music map
     *
     * @param  key_name the key of the font
     */
    Mix_Music* getMixMusicResource(std::string key_name);
    /**
     * @brief Get the sound resource from a sound map
     *
     * @param  key_name the key of the sound
     */
    Mix_Chunk* getChunkResource(std::string key_name);

    /** languages available  */
    std::map< std::string, std::map<std::string, std::string> > getLanguageMaps();
    /** current language map */
    std::map<std::string, std::string> getCurrentLanguageMap();

    /**
     * @brief Set current language map
     */
    void setCurrentLanguageMap(std::string languageSelected);
    /**
     * @brief Load language pack from file
     */
    std::map<std::string, std::string> loadLanguagePack(std::string path);
    /**
     * @brief Load language resource
     */
    bool loadLanguageResource();

    string getCurrentWorkingDirectory();



private:
    /**
     * @brief Default constructor
     */
    ResourceManager();
    /** the only resource manager instance */
    static ResourceManager* g_resourceManager;

    // the Texture we create
    // LTexture* gImage = new LTexture();

    SDL_Surface* surface = NULL; /**< the surface we create texture from */
    TTF_Font* gFont = NULL; /**< the font we create */
    Mix_Music *gMusic = NULL; /**< The music that will be played */
    Mix_Chunk *gSound = NULL; /**< The sound effects that will be used */

    /** the map from string to LTexture */
    std::map<std::string, LTexture*> textureResource;
    /** the map from string to ture type font texture */
    std::map<std::string, TTF_Font*> fontResource;
    /** the map from string to Mix_Music */
    std::map<std::string, Mix_Music*> musicResource;
    /** the map from string to Mix_Chunk (Sound Effect) */
    std::map<std::string, Mix_Chunk*> chunkResource;

    std::map< std::string, std::map<std::string, std::string> > languageMaps; /**< languages available */
    std::map<std::string, std::string> currentLanguageMap; /**< current language map */

};

#endif
