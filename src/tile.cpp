//
//  Tile.cpp
//
//
//  Created by Tianxiang Dai on 3/14/18.
//

#include "../include/tile.h"

Tile::Tile() : Collider(this), tileId(0), index(-1), tileType(TILE_TYPE_BASIC) {
    this->tag = "TILE_TYPE_BASIC";
}

Tile::Tile( Vector2D pos ) : Collider(this), tileId(0), index(-1), tileType(TILE_TYPE_BASIC) {
    setPosition( pos );
}

Tile::Tile( Vector2D pos, Vector2D vel ) : Collider(this), tileId(0), index(-1), tileType(TILE_TYPE_BASIC) {
    setPosition( pos );
    setVelocity( vel );
}

Tile::~Tile(){

}

void Tile::setTileId( int tileId ){
    this->tileId = tileId;
}

void Tile::setTileType( int tileType ){
    this->tileType = tileType;
}

void Tile::setIndex( int index ){
    this->index = index;
}

int Tile::getTileType(){
    return tileType;
}

int Tile::getTileId(){
    return tileId;
}

int Tile::getIndex(){
    return index;
}
