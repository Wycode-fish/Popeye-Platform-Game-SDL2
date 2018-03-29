//
//  TileMapSystem.cpp
//
//
//  Created by Tianxiang Dai on 3/14/18.
//

#include "../include/tilemapsystem.h"

TileMapSystem* TileMapSystem::gTileMapSystem = NULL;

TileMapSystem* TileMapSystem::getInstance(){
    if ( !gTileMapSystem )
        gTileMapSystem = new TileMapSystem();
    return gTileMapSystem;
}

TileMapSystem::TileMapSystem(): currentMapId( 0 ) {
    // do nothing
}

TileMapSystem::~TileMapSystem(){
    if ( !tileMapList.empty() ){
        for (vector<TileMap*>::iterator it = tileMapList.begin();
             it != tileMapList.end();
             it ++){
            delete []*it;
        }
        tileMapList.clear();
    }
}

bool TileMapSystem::onLoad( const string& fileName, vector<int> groundIndexSet, vector<int> specialIndexSet, int mapType,
                            Vector2D specialAccEffect,
                            Vector2D inputFactorEffect,
                            int specialLifeEffect,
                            vector<int> checkPointList,
                            Vector2D passPoint ){
    bool success = true;

    int currentId = tileMapList.size();

    vector<Vector2D> checkPointVec;

    ifstream inFile;
    string imagePath = "";
    string tilePath = "";
    int width = 0;
    int height = 0;
    int tileWidth = 0;
    int tileHeight = 0;
    inFile.open(fileName);
    if(!inFile){
        char path[2000];
        getcwd(path, sizeof(path));
        string str(path);
        cout << "Unable to open file : " << fileName << endl;
        cout << "Current Work Directory !\n" << path << endl;
        cerr << "Error: " << strerror(errno);
        return false;
    }
    // First, read the map image path
    getline(inFile, imagePath);
    getline(inFile, tilePath);
    inFile >> tileWidth;
    inFile >> tileHeight;
    inFile >> width;
    inFile >> height;
    //    cout << "Image Path : " << imagePath << endl;
    //    cout << "Tile Path : " << tilePath << endl;
    //    cout << "Tile Width : " << tileWidth << endl;
    //    cout << "Tile Height : " << tileHeight << endl;
    //    cout << "Width : " << width << endl;
    //    cout << "Height : " << height << endl;
    TileMap* tileMap = new TileMap();
    tileMap->setMapId( currentId );
    tileMap->setMapType( mapType );
    tileMap->setMapWidth( width );
    tileMap->setMapHeight( height );
    tileMap->setTileWidth( tileWidth );
    tileMap->setTileHeight( tileHeight );
    tileMap->setSpecialAccEffect( specialAccEffect );
    tileMap->setInputFactorEffect( inputFactorEffect );
    tileMap->setSpecialLifeEffect( specialLifeEffect );
    tileMap->setPassPoint( passPoint );
    while(!inFile.eof()){
        int index = 0;
        inFile >> index;
        Tile* tile = new Tile();
        tile->setBoundingBox( Vector2D( TILE_INITIAL_WIDTH, TILE_INITIAL_HEIGHT ) );
        tile->setIndex(index);
        if (tileMap->getTileList().size() == width * height)
            break;
        // set tile id
        tile->setTileId( tileMap->getTileList().size() );
        // set tile pos
        int tileXOffset = tile->getTileId() % width;
        int tileYOffset = tile->getTileId() / width;
        float tilePosX = ( tileXOffset + 0.5f ) * tileWidth;
        float tilePosY = ( tileYOffset + 0.5f ) * tileHeight;
        tile->setPosition( Vector2D( tilePosX, tilePosY ) );
        // set tile type
        bool isGround = false;
        bool isSpecial = false;
        bool isCheckPoint = false;
        for (int i = 0; i < groundIndexSet.size(); i++){
            if ( groundIndexSet[i] == index ){
                isGround = true;
                break;
            }
        }

        for (int i = 0; i < specialIndexSet.size(); i++){
            if ( specialIndexSet[i] == index ){
                isSpecial = true;
                break;
            }
        }

        for (int i = 0; i < checkPointList.size(); i++){
            if ( checkPointList[i] == index ){
                isCheckPoint = true;
                break;
            }
        }

        if ( isGround ){
            tile->setTileType( TILE_TYPE_SURFACE );
            tile->setTag( "TILE_TYPE_SURFACE" );
        } else if (isSpecial){
            tile->setTileType( TILE_TYPE_SPECIAL );
            tile->setTag( "TILE_TYPE_SPECIAL" );
        } else if (isCheckPoint){
            tile->setTileType( TILE_TYPE_BASIC );
            tile->setTag( "TILE_TYPE_BASIC" );
            checkPointVec.push_back( Vector2D( tile->getPosition()[0], tile->getPosition()[1] ) );
        } else {
            tile->setTileType( TILE_TYPE_BASIC );
            tile->setTag( "TILE_TYPE_BASIC" );
        }
        tileMap->addTile(tile);
    }
    tileMap->setCheckPointList(checkPointVec);
    tileMapList.push_back( tileMap );
    // cout << "Read TileMap Size From File : " << tileMap.size() << endl;

    inFile.close();
    return success;
}

TileMap* TileMapSystem::getTileMap( int mapId ){
    cout << "Get Tile Map \n";
    if ( mapId >= tileMapList.size() ){
        cout << "mapId oversize !\n";
        return NULL;
    }
    return tileMapList[mapId];
}

bool TileMapSystem::init(){
    bool success = true;
    // here onLoad all the map
    return success;
}

bool TileMapSystem::quit(){
    // do nothing
    bool success = true;
    return success;
}
void TileMapSystem::update(){
    // do nothing
}

void TileMapSystem::setCurrentMapId( int currentMapId ){
    this->currentMapId = currentMapId;
}

int TileMapSystem::getCurrentMapId(){
    return currentMapId;
}
