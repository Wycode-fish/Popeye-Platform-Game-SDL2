#ifndef TILEMAP_H
#define TILEMAP_H


#include "tile.h"
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
    void setSpecialAccEffect( Vector2D specialAccEffect );
    void setSpecialLifeEffect( int specialLifeEffect );
    void setInputFactorEffect( Vector2D inputFactorEffect );
    void setCheckPointList( vector<Vector2D> checkPointList );
    void setPassPoint( Vector2D passPoint );
    int getMapId();
    Tile* tileAtPos( Vector2D pos );
    Tile* tileAtLeftPos( Vector2D pos );
    Tile* tileAtRightPos( Vector2D pos );
    Tile* tileAtUpPos( Vector2D pos );
    Tile* tileAtDownPos( Vector2D pos );
    vector<Tile*> tileAtVerticalPos( Vector2D pos );
    vector<Tile*> tileAtHorizontalPos( Vector2D pos );
    Tile* getTile( int tileId );
    Vector2D getSpecialAccEffect( );
    Vector2D getInputFactorEffect();
    int getSpecialLifeEffect();
    int getMapType();
    int getTileWidth();
    int getTileHeight();
    int getWidth();
    int getHeight();
    vector<Vector2D> getCheckPointList();
    Vector2D getPassPoint();
private:
    vector<Tile*> tileList;
    int mapId;
    int mapWidth; // in tiles
    int mapHeight; // in tiles
    int tileWidth; // in pixel
    int tileHeight; // in pixel
    int typeId;
    Vector2D specialAccEffect; // the special Effect to accleration factors in each map
    int specialLifeEffect; //  the special Effect to life factor in each map
    Vector2D inputFactorEffect; // the input factor effect in each map
    vector<Vector2D> checkPointList;
    Vector2D passPoint;
};

#endif // TILEMAP_H
