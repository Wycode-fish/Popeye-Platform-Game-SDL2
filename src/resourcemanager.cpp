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
//    QString sEnFile = QApplication::applicationDirPath() + "/Assets/languages/english.txt";
//
//    QString sChFile = QApplication::applicationDirPath() + "/Assets/languages/chinese.txt";
//
//    std::map<std::string, std::string> en2enMap = loadLanguagePack(sEnFile.toStdString());
//    std::map<std::string, std::string> en2cnMap = loadLanguagePack(sChFile.toStdString());
    
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

    loadTileMapResource();
    
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
    bool texture_load_success = loadTextureResource(renderer, "Assets/images/hero_final.png", "texture_hero") &&
    loadTextureResource(renderer, "Assets/maps/res/snowscene.png", "texture_map_snowscene") &&
    loadTextureResource(renderer, "Assets/maps/res/kungfu.png", "texture_map_kungfu") &&
    loadTextureResource(renderer, "Assets/maps/res/old_castle.png", "texture_map_old_castle") &&
    loadTextureResource(renderer, "Assets/images/minions.png", "texture_minion") &&
    loadTextureResource(renderer, "Assets/images/powerup_test_2.png", "texture_powerup") &&
    loadTextureResource(renderer, "Assets/images/bullet_blade.png", "texture_bullet") &&
    loadTextureResource(renderer, "Assets/images/collectible.png", "texture_collectible") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_setting_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_main_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_instruction_menu_button_sprite_sheet")&&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_pass_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_pause_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_lose_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/menus/blueSheet.png", "texture_win_menu_button_sprite_sheet") &&
    loadTextureResource(renderer, "Assets/images/powerUpIcon.png", "texture_powerup_icon") &&
    loadTextureResource(renderer, "Assets/images/checkPoint.png", "texture_check_point");

    if (!texture_load_success) printf("texture loading error.\n");
    
     //load fonts.
     bool font_load_success = loadTureTypeFontResource(renderer, "Assets/fonts/chinese.ttf", 30, "font_main");
     if (!font_load_success) printf("font loading error.\n");
    
     //load music.
     bool music_load_success = loadMixMusicResource( "Assets/music/kungfu.mp3", "kungfu_background" ) &&
             loadMixMusicResource( "Assets/music/mainmenu.mp3", "mainmenu_background" ) &&
             loadMixMusicResource( "Assets/music/snowscene.mp3", "snowscene_background" ) &&
             loadMixMusicResource( "Assets/music/oldcastle.mp3", "oldcastle_background" );

     if (!music_load_success) printf("music loading error.\n");
    
    // load sound effects.
     bool sound_load_success = loadChunkResource("Assets/sound/passSound.wav", "pass_sound") &&
             loadChunkResource("Assets/sound/FireSound.wav", "fire_sound") &&
             loadChunkResource("Assets/sound/PowerUpSound2.mp3", "powerup_sound") &&
             loadChunkResource("Assets/sound/WinSound.wav", "win_sound") &&
             loadChunkResource("Assets/sound/JumpSound.mp3", "jump_sound") &&
             loadChunkResource("Assets/sound/LoseSound.wav", "lose_sound") &&
             loadChunkResource("Assets/sound/CollectibleSound.wav", "collectible_sound")&&
             loadChunkResource("Assets/sound/KickSound.wav", "kick_sound") &&
             loadChunkResource("Assets/sound/CheckPointSound.wav", "check_point_sound");



//             loadChunkResource("../Assets/sound/PowerUpSound2.mp3", "powerup_sound");

     if (!sound_load_success) printf("sound loading error.\n");
    
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

string ResourceManager::getCurrentWorkingDirectory(void)
{
    char path[1024];
    getcwd(path, sizeof(path));
    string str(path);
    return str;
}

bool ResourceManager::loadTileMapResource(){
    /******     For TileMap Initialization      *****/
    bool success = true;
    {
        //generate the file path
//        QString sFile = QApplication::applicationDirPath() + "/Assets/maps/info/snowscene.txt";
//        string fileName = sFile.toStdString();
        string fileName = "";
        fileName = fileName + getCurrentWorkingDirectory() + "/" + "assets/maps/info/snowscene.txt";
        cout << "File Directory : " << fileName << endl;
        //fileName = "../Assets/maps/info/snowscene.txt";
        int groundIndexArray[] = {0, 1, 21, 22, 23};
        int specialIndexArray[] = {2};
        int checkPointArray[] = {7, 8};
        vector<int> groundIndexSet (groundIndexArray, groundIndexArray + sizeof(groundIndexArray) / sizeof(int));
        vector<int> specialIndexSet (specialIndexArray, specialIndexArray + sizeof(specialIndexArray) / sizeof(int));
        vector<int> checkPointList (checkPointArray, checkPointArray + sizeof(checkPointArray) / sizeof(int));
        TileMapSystem::getInstance()->onLoad( fileName,
                                              groundIndexSet,
                                              specialIndexSet,
                                              MAP_TYPE_NORMAL,
                                              Vector2D(0.0f, 0.0f),
                                              Vector2D(0.2f, 1.0f),
                                              0,
                                              checkPointList,
                                              Vector2D( 3532.5, 337.5 ));
    }

    {
        //generate the file path
//        QString sFile = QApplication::applicationDirPath() + "/Assets/maps/info/kungfu.txt";
//        string fileName = sFile.toStdString();
        string fileName = "";
        fileName = fileName + getCurrentWorkingDirectory() + "/" + "assets/maps/info/kungfu.txt";
        cout << "File Directory : " << fileName << endl;
        int groundIndexArray[] = {18, 19, 20, 21};
        int specialIndexArray[] = {};
        int checkPointArray[] = {9, 10, 11};
        vector<int> groundIndexSet (groundIndexArray, groundIndexArray + sizeof(groundIndexArray) / sizeof(int));
        vector<int> specialIndexSet (specialIndexArray, specialIndexArray + sizeof(specialIndexArray) / sizeof(int));
        vector<int> checkPointList (checkPointArray, checkPointArray + sizeof(checkPointArray) / sizeof(int));
        TileMapSystem::getInstance()->onLoad( fileName,
                                              groundIndexSet,
                                              specialIndexSet,
                                              MAP_TYPE_NORMAL,
                                              Vector2D(0.0f, 0.0f),
                                              Vector2D(1.0f, 1.0f),
                                              0,
                                              checkPointList,
                                              Vector2D( 3577.5, 382.5 ));
    }

    {
        //generate the file path
//        QString sFile = QApplication::applicationDirPath() + "/Assets/maps/info/old_castle.txt";
//        string fileName = sFile.toStdString();
        string fileName = "";
        fileName = fileName + getCurrentWorkingDirectory() + "/" + "assets/maps/info/old_castle.txt";
        cout << "File Directory : " << fileName << endl;
        int groundIndexArray[] = {0, 1};
        int specialIndexArray[] = {11};
        int checkPointArray[] = {2, 3};
        vector<int> groundIndexSet (groundIndexArray, groundIndexArray + sizeof(groundIndexArray) / sizeof(int));
        vector<int> specialIndexSet (specialIndexArray, specialIndexArray + sizeof(specialIndexArray) / sizeof(int));
        vector<int> checkPointList (checkPointArray, checkPointArray + sizeof(checkPointArray) / sizeof(int));
        TileMapSystem::getInstance()->onLoad( fileName,
                                              groundIndexSet,
                                              specialIndexSet,
                                              MAP_TYPE_NORMAL,
                                              Vector2D(0.0f, 0.0f),
                                              Vector2D(1.0f, 1.0f),
                                              1,
                                              checkPointList,
                                              Vector2D( 112.5 , 652.5 ));
    }
    return success;
}
