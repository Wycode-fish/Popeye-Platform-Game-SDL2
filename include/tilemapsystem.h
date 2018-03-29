#ifndef TILEMAPSYSTEM_H
#define TILEMAPSYSTEM_H

#include "tilemap.h"
#include "system.h"
#include <fstream>
#include <unistd.h>

using namespace std;

// This class represents the tilemap manager
// Singleton

class TileMapSystem : public System {
public:
    static TileMapSystem* getInstance();
    ~TileMapSystem();
    bool onLoad( const string& fileName, vector<int> groundIndexSet, vector<int> specialIndexSet, int mapType,
                 Vector2D specialEffect,
                 Vector2D inputFactorEffect,
                 int specialLifeEffect,
                 vector<int> checkPointList,
                 Vector2D passPoint );
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
