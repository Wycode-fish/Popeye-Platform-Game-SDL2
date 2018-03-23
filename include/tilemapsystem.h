#ifndef TILEMAPSYSTEM_H
#define TILEMAPSYSTEM_H


#include "tilemap.h"
#include "system.h"
#include <fstream>
using namespace std;

// This class represents the tilemap manager
// Singleton

class TileMapSystem : public System {
public:
    static TileMapSystem* getInstance();
    ~TileMapSystem();
    bool onLoad( const string& fileName, vector<int> groundIndexSet, int mapType );
    TileMap* getTileMap( int mapId );
    void setCurrentMapId( int currentMapId );
    int getCurrentMapId();
    bool init();
    bool quit();
    void update();
private:
    static TileMapSystem* gTileMapSystem;
    TileMapSystem();
    vector<TileMap*> tileMapList;
    int currentMapId;
};


#endif // TILEMAPSYSTEM_H
