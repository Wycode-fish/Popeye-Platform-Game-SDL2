#ifndef TILE_H
#define TILE_H


// This class represents the tile class
#include "constants.h"
#include "collider.h"
#include "gameobject.h"


class Tile : public Collider, public GameObject {
public:
   Tile();
   Tile( Vector2D pos );
   Tile( Vector2D pos, Vector2D vel );
   ~Tile();
   void setTileId( int tileId );
   void setTileType( int tileType );
   void setIndex( int index );
   int getTileType();
   int getTileId();
   int getIndex();
private:
   int tileId;
   int index; // the type id, to be rendered
   int tileType; //  the type, ground or not ground

};


#endif // TILE_H
