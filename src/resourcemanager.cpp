#include "../include/resourcemanager.h"

ResourceManager* ResourceManager::g_resourceManager = NULL;

// getInstance()
ResourceManager* ResourceManager::getInstance(){
    if ( !g_resourceManager )
    g_resourceManager = new ResourceManager();
    return g_resourceManager;
}

// Default Constructor
ResourceManager::ResourceManager(){
    // Do nothing
}

// Default Destructor
ResourceManager::~ResourceManager(){
    // Do nothing
}

// Load LTexture resource
bool ResourceManager::loadTextureResource( SDL_Renderer* renderer, const char* path, std::string key_name ){
    LTexture* gImage = new LTexture();
    if ( textureResource[key_name] == NULL ){
        if ( !gImage->loadFromFile( path, renderer )){
            SDL_Log( "Unable to load Image!\n" );
            return false;
        } else {
            textureResource[key_name] = gImage;
        }
    }
    return true;
}

// Load Ture Type Font resource
bool ResourceManager::loadTureTypeFontResource( SDL_Renderer* renderer, const char* path, int size, std::string key_name ){
    if ( fontResource[key_name] == NULL ){
        gFont = TTF_OpenFont( path, size );
        if ( gFont == NULL ){
            SDL_Log( "Failed to open font!\n" );
            return false;
        }
        else
        fontResource[key_name] = gFont;
    }
    return true;
}

// Load Music resource
bool ResourceManager::loadMixMusicResource( const char* path, std::string key_name ){
    if ( musicResource[key_name] == NULL ){
        gMusic = Mix_LoadMUS( path );
        if ( gMusic == NULL ){
            SDL_Log( "Failed to open music!\n" );
            return false;
        }
        else
        musicResource[key_name] = gMusic;
    }
    return true;
}

// Load Chunk resource
bool ResourceManager::loadChunkResource( const char* path, std::string key_name ){
    if ( chunkResource[key_name] == NULL ){
        gSound = Mix_LoadWAV( path );
        if ( gSound == NULL ){
            SDL_Log( "Failed to open chunk!\n" );
            return false;
        }
        else
        chunkResource[key_name] = gSound;
    }
    return true;
}



std::map<std::string, std::string> ResourceManager::loadLanguagePack(std::string path) {
    
    // A map to store strings
    std::map<std::string, std::string> languageMap;
    // Load language pack from file
    ifstream fin(path);
    if (!fin.good()) {
        languageMap.insert(std::pair<std::string, std::string>("start", "Start"));
        languageMap.insert(std::pair<std::string, std::string>("setting", "Setting"));
        languageMap.insert(std::pair<std::string, std::string>("life", "Life"));
        languageMap.insert(std::pair<std::string, std::string>("score", "Score"));
        languageMap.insert(std::pair<std::string, std::string>("level", "Level"));
        return languageMap;
    }
    
    std::string s;
    
    while (getline(fin,s)) {
        size_t pos = s.find("=");
        std::string key = s.substr(0, pos);
        std::string value = s.substr(pos+1, string::npos);
        
        languageMap.insert(std::pair<std::string, std::string>(key, value));
    }
    
    return languageMap;
    
}

bool ResourceManager::loadLanguageResource() {
    std::map<std::string, std::string> en2enMap = loadLanguagePack("Assets/languages/english.txt");
    std::map<std::string, std::string> en2cnMap = loadLanguagePack("Assets/languages/chinese.txt");
    languageMaps.insert(std::pair< std::string, std::map<std::string, std::string> >("english", en2enMap));
    languageMaps.insert(std::pair< std::string, std::map<std::string, std::string> >("chinese", en2cnMap));
    return true;
}

std::map< std::string, std::map<std::string, std::string> > ResourceManager::getLanguageMaps() {
    return languageMaps;
}
std::map<std::string, std::string> ResourceManager::getCurrentLanguageMap() {
    return currentLanguageMap;
}

void ResourceManager::setCurrentLanguageMap(std::string languageSelected) {
    currentLanguageMap = languageMaps[languageSelected];
}




bool ResourceManager::init(){
    // Now do nothing
    bool success = true;
    return success;
}

// init
bool ResourceManager::init(SDL_Renderer* renderer){
    
    
    loadLanguageResource();
    
    if (CURRENT_LANGUAGE==LANGUAGE_CHINESE)
    ResourceManager::setCurrentLanguageMap("chinese");
    
    if (CURRENT_LANGUAGE==LANGUAGE_ENGLISH)
    ResourceManager::setCurrentLanguageMap("english");
    
    
    // load textures.
    // bool texture_load_success = loadTextureResource(renderer, "hero.png", "texture_hero") &&
    //                             loadTextureResource(renderer, "test1.png", "texture_map") &&
    //                             loadTextureResource(renderer, "minion.png", "texture_minion") &&
    //                             loadTextureResource(renderer, "Assets/images/powerup.png", "texture_powerup") &&
    //                             loadTextureResource(renderer, "Assets/images/bullet.png", "texture_bullet");
    bool texture_load_success = loadTextureResource(renderer, "Assets/images/hero.png", "texture_hero") &&
    loadTextureResource(renderer, "Assets/maps/res/test2.png", "texture_map") &&
    loadTextureResource(renderer, "Assets/images/minions.png", "texture_minion") &&
    loadTextureResource(renderer, "Assets/images/powerups.png", "texture_powerup") &&
    loadTextureResource(renderer, "Assets/images/bullets.png", "texture_bullet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_setting_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_main_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_instruction_menu_button_sprite_sheet")&&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_pass_menu_button_sprite_sheet");
    if (!texture_load_success) printf("texture loading error.\n");
    
     //load fonts.
     bool font_load_success = loadTureTypeFontResource(renderer, "Assets/fonts/chinese.ttf", 30, "font_main");
     if (!font_load_success) printf("font loading error.\n");
    
    // load music.
    // bool music_load_success = loadMixMusicResource( "../Assets/music/background.mp3", "music_background" );
    // if (!music_load_success) printf("music loading error.\n");
    
    // load sound effects.
    // bool sound_load_success =
    // loadChunkResource("../Assets/sound/GameOver_SFX.mp3", "sound_gameover") &&
    // loadChunkResource("../Assets/sound/BrickHit_SFX.mp3", "sound_ball_hit_brick") &&
    // loadChunkResource("../Assets/sound/PaddleBorderHit_SFX.mp3", "sound_paddle_hit_border");
    // if (!sound_load_success) printf("sound loading error.\n");
    
    std::cout << "ResourceManager Init ! \n";
    
    // return texture_load_success && font_load_success && music_load_success && sound_load_success;
    return texture_load_success;
}


// getters.
LTexture* ResourceManager::getTextureResource(std::string key_name) {
    return textureResource[key_name];
}

TTF_Font* ResourceManager::getTureTypeFontResource(std::string key_name) {
    return fontResource[key_name];
}

Mix_Music* ResourceManager::getMixMusicResource(std::string key_name) {
    return musicResource[key_name];
}

Mix_Chunk* ResourceManager::getChunkResource (std::string key_name) {
    return chunkResource[key_name];
}


// update
void ResourceManager::update(){
    // Now do nothing
}


// quit
bool ResourceManager::quit(){
    // In quit, we destroy SDL_Surface* and all the textures and music resources
    bool success = true;
    // Free gFont
    TTF_CloseFont( gFont );
    gFont = NULL;
    // Free gMusic
    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    // Free gChunk
    Mix_FreeChunk( gSound );
    gSound = NULL;
    
    // Free textureResource
    for ( std::map<std::string, LTexture*>::iterator it = textureResource.begin();
         it != textureResource.end();
         it++)
    {
        it->second->free();
    }
    
    // Free fontResource
    for ( std::map<std::string, TTF_Font*>::iterator it = fontResource.begin();
         it != fontResource.end();
         it++)
    {
        TTF_CloseFont( it->second );
    }
    
    // Free musicResource
    for ( std::map<std::string, Mix_Music*>::iterator it = musicResource.begin();
         it != musicResource.end();
         it++)
    {
        Mix_FreeMusic( it->second );
    }
    
    // Free chunkResource
    for ( std::map<std::string, Mix_Chunk*>::iterator it = chunkResource.begin();
         it != chunkResource.end();
         it++)
    {
        Mix_FreeChunk( it->second );
    }
    
    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    return success;
}
