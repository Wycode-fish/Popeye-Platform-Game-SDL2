#include "../include/camera.h"

Camera* Camera::cameraInstance = NULL;

Camera::Camera() {
    focus = NULL;
}

Camera::Camera(int mode) {
    setCameraMode(mode);
}

Camera::~Camera() {}


Camera* Camera::getInstance() {

    if (cameraInstance == NULL) {
        cameraInstance = new Camera();
    }
    return cameraInstance;
}


void Camera::setCameraMode (int m) {
    mode = m;
}


int Camera::getCameraMode () {
    return mode;
}


Vector2D Camera::getCameraPos() {
    if (focus != NULL) {

        if ( mode == CAMERA_MODE_CENTER) {
            return *focus - Vector2D(WINDOW_HEIGHT/2, WINDOW_WIDTH/2);
        }

        return *focus;
    }

    return position;
}

void Camera::setCameraPos(Vector2D pos) {

    position = pos;
}

void Camera::setFocus(Vector2D* f) {

    focus = f;
}

Vector2D* Camera::getFocus() {

    return focus;
}

void Camera::onMove(Vector2D incre) {

    Vector2D pos = getCameraPos();

    Vector2D newPos = pos + incre;

//    if ((newPos[0] + WINDOW_WIDTH/2)>MAP_WIDTH) newPos[0] = MAP_WIDTH-WINDOW_WIDTH/2;
//    if ((newPos[0] - WINDOW_WIDTH/2)<0) newPos[0] = MAP_WIDTH-WINDOW_WIDTH/2;
//    if ((newPos[1] + WINDOW_WIDTH/2)>MAP_HEIGHT) newPos[1] = MAP_HEIGHT-WINDOW_HEIGHT/2;
//    if ((newPos[1] + WINDOW_WIDTH/2)<0) newPos[1] = WINDOW_HEIGHT/2;

    setCameraPos(newPos);
}

void Camera::update() {

    Vector2D heroPos = GameSetting::getInstance()->getHero()->getPosition();

    TileMap* currentMap = TileMapSystem::getInstance()->getTileMap( TileMapSystem::getInstance()->getCurrentMapId() );

    int mapWidth = currentMap->getWidth() * currentMap->getTileWidth();
    int mapHeight = currentMap->getHeight() * currentMap->getTileHeight();

    float offX = heroPos[0]-CAMERA_OFFSET_FROM_HERO_X;
    float offY = heroPos[1]-CAMERA_OFFSET_FROM_HERO_Y;
    if (offX <= 0.0f)
        offX = 0.0f;
    if (offY <= 0.0f)
        offY = 0.0f;
    if (offX >= mapWidth - WINDOW_WIDTH)
        offX = mapWidth - WINDOW_WIDTH;
    if (offY >= mapHeight - WINDOW_HEIGHT)
        offY = mapHeight - WINDOW_HEIGHT;
    Vector2D cPos = Vector2D(offX, offY);

    setCameraPos(cPos);
}
