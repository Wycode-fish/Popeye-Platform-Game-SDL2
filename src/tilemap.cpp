//
//  TileMap.cpp
//
//
//  Created by Tianxiang Dai on 3/14/18.
//

#include "../include/tilemap.h"

TileMap::TileMap(){

}

TileMap::~TileMap(){
    if ( !tileList.empty() ){
        for (vector<Tile*>::iterator it = tileList.begin();
             it != tileList.end();
             it++){
            Tile* temp = *it;
            delete []temp;
        }
    }
    tileList.clear();
}

void TileMap::addTile( Tile* tile ){
    tileList.push_back( tile );
}

vector<Tile*> TileMap::getTileList(){
    return tileList;
}

void TileMap::setMapId( int mapId ){
    this->mapId = mapId;
}

void TileMap::setMapType( int mapType ){
    typeId = mapType;
}

int TileMap::getMapId(){
    return mapId;
}

int TileMap::getMapType(){
    return typeId;
}


//Tile* TileMap::tileAtPos( Vector2D pos ){// pos is the hero Pos in map coordinate
//    // return the closet tile under the hero position
//    //Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
//    Vector2D heroPos = pos; // the hero position, relative to window coordinate
//    Vector2D heroIndex = Vector2D( heroPos[0] / tileWidth , heroPos[1] / tileHeight );
//    int tileId = floor(heroIndex[0]) + floor((heroIndex[1] + 1)) * mapWidth;
////    cout << "Tile Size : " << tileWidth << " " << tileHeight << endl;
////    cout << "Map Size (in tiles) : " << mapWidth << " " << mapHeight << endl;
////    cout << "Camera Pos : " << cameraPos[0] << " " << cameraPos[1] << endl;
////    cout << "Hero Pos : " << heroPos[0] << " " << heroPos[1] << endl;
////    cout << "Tile Id : " << tileId << endl;
//    return getTile( tileId );
//}

Tile* TileMap::tileAtLeftPos( Vector2D pos ){// pos is the object Pos in map coordinate
    // return the closet tile under the hero position
    Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
    Vector2D heroPos = pos; // the hero position, relative to window coordinate
    Vector2D heroIndex = Vector2D( heroPos[0] / tileWidth , heroPos[1] / tileHeight );
    int tileId = floor(heroIndex[0]) + floor(heroIndex[1]) * mapWidth - 1;
    return getTile( tileId );
}

Tile* TileMap::tileAtRightPos( Vector2D pos ){// pos is the object Pos in map coordinate
    // return the closet tile under the hero position
    Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
    Vector2D heroPos = pos; // the hero position, relative to window coordinate
    Vector2D heroIndex = Vector2D( heroPos[0] / tileWidth , heroPos[1] / tileHeight );
    int tileId = floor(heroIndex[0]) + floor(heroIndex[1]) * mapWidth + 1;
    return getTile( tileId );
}

Tile* TileMap::tileAtUpPos( Vector2D pos ){// pos is the object Pos in map coordinate
    // return the closet tile under the hero position
    Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
    Vector2D heroPos = pos; // the hero position, relative to window coordinate
    Vector2D heroIndex = Vector2D( heroPos[0] / tileWidth , heroPos[1] / tileHeight );
    int tileId = floor(heroIndex[0]) + floor( (heroIndex[1] - 1) ) * mapWidth;
    return getTile( tileId );
}

Tile* TileMap::tileAtDownPos( Vector2D pos ){// pos is the object Pos in map coordinate
    // return the closet tile under the hero position
    Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
    Vector2D heroPos = pos; // the hero position, relative to window coordinate
    Vector2D heroIndex = Vector2D( heroPos[0] / tileWidth , heroPos[1] / tileHeight );
    int tileId = floor(heroIndex[0]) + floor( (heroIndex[1] + 1) ) * mapWidth;
    return getTile( tileId );
}

//vector<Tile*> TileMap::tileAtVerticalPos( Vector2D pos ){// pos is the Pos in map coordinate system
//    // return the closet tile under the hero position
//    //Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
//    Vector2D objectPos = pos; // the hero position, relative to window coordinate
//    Vector2D objectIndex = Vector2D( objectPos[0] / tileWidth , objectPos[1] / tileHeight );


//    int tileId1 = floor(objectIndex[0]) + floor((objectIndex[1] + 1)) * mapWidth;
//    int tileId2 = floor(objectIndex[0]) + floor((objectIndex[1] - 1)) * mapWidth;
////   cout << "Tile Size : " << tileWidth << " " << tileHeight << endl;
////   cout << "Map Size (in tiles) : " << mapWidth << " " << mapHeight << endl;
////   cout << "Camera Pos : " << cameraPos[0] << " " << cameraPos[1] << endl;
////   cout << "Hero Pos : " << heroPos[0] << " " << heroPos[1] << endl;
////   cout << "Tile Id : " << tileId << endl;
//    Tile* tileTop = getTile(tileId1);
//    Tile* tileBottom = getTile(tileId2);
//    vector<Tile*> verticalTiles;
//    verticalTiles.push_back(tileTop);
//    verticalTiles.push_back(tileBottom);
//    return verticalTiles;
//}

//vector<Tile*> TileMap::tileAtHorizontalPos( Vector2D pos ){// pos is the hero Pos in window coordinate
//    // return the closet tile under the hero position
//    //Vector2D cameraPos = Camera::getInstance()->getCameraPos(); // the camera position, relative to map, in the left-top corner
//    Vector2D objectPos = pos; // the hero position, relative to window coordinate
//    Vector2D objectIndex = Vector2D( objectPos[0] / tileWidth , objectPos[1] / tileHeight );
//    int tileId = floor(objectIndex[0]) + floor((objectIndex[1] + 1)) * mapWidth;

//    int tileId1 = tileId - 1;
//    int tileId2 = tileId + 1;
////   cout << "Tile Size : " << tileWidth << " " << tileHeight << endl;
////   cout << "Map Size (in tiles) : " << mapWidth << " " << mapHeight << endl;
////   cout << "Camera Pos : " << cameraPos[0] << " " << cameraPos[1] << endl;
////   cout << "Hero Pos : " << heroPos[0] << " " << heroPos[1] << endl;
////   cout << "Tile Id : " << tileId << endl;
//    Tile* tileLeft = getTile(tileId1);
//    Tile* tileRight = getTile(tileId2);
//    vector<Tile*> horizontalTiles;
//    horizontalTiles.push_back(tileLeft);
//    horizontalTiles.push_back(tileRight);
//    return horizontalTiles;
//}

Tile* TileMap::getTile( int tileId ){
    if ( tileId >= tileList.size() ){
        cout << "TileList[tileId] is NULL\n";
        return NULL;
    }
//    cout << "Get Tile Pos : " << tileList[tileId]->getPosition()[0] << " " << tileList[tileId]->getPosition()[1] << endl;
    return tileList[tileId];
}

void TileMap::setMapWidth( int mapWidth ){
    this->mapWidth = mapWidth;
}

void TileMap::setMapHeight( int mapHeight ){
    this->mapHeight = mapHeight;
}

void TileMap::setTileHeight( int tileHeight ){
    this->tileHeight = tileHeight;
}

void TileMap::setTileWidth( int tileWidth ){
    this->tileWidth = tileWidth;
}
