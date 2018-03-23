#ifndef TILEMAP_H
#define TILEMAP_H


#include "tile.h"
#include "camera.h"
#include <vector>
#include <iostream>


using namespace std;

// This class represents the tile map
class TileMap{
public:
    TileMap();
    ~TileMap();
    void addTile( Tile* tile );
    vector<Tile*> getTileList();
    void setMapId( int mapId );
    void setMapType( int mapType );
    void setMapWidth( int mapWidth );
    void setMapHeight( int mapHeight );
    void setTileHeight( int tileHeight );
    void setTileWidth( int tileWidth );
    int getMapId();
    Tile* tileAtPos( Vector2D pos );
    Tile* tileAtLeftPos( Vector2D pos );
    Tile* tileAtRightPos( Vector2D pos );
    Tile* tileAtUpPos( Vector2D pos );
    Tile* tileAtDownPos( Vector2D pos );
    vector<Tile*> tileAtVerticalPos( Vector2D pos );
    vector<Tile*> tileAtHorizontalPos( Vector2D pos );
    Tile* getTile( int tileId );
    int getMapType();
private:
    vector<Tile*> tileList;
    int mapId;
    int mapWidth; // in tiles
    int mapHeight; // in tiles
    int tileWidth; // in pixel
    int tileHeight; // in pixel
    int typeId;
};

#endif // TILEMAP_H
