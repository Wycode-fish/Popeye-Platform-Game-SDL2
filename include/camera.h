#ifndef CAMERA_H
#define CAMERA_H

#include "vector2d.h"
#include "gamesetting.h"
#include "constants.h"
#include "tilemapsystem.h"

class Camera {

public:

    ~Camera();

public:

    static Camera*		getInstance();

    Vector2D* 			getFocus();

    void 				setFocus(Vector2D* f);

    int 				getCameraMode();

    void 				setCameraMode(int mode);

    Vector2D			getCameraPos();

    void				setCameraPos(Vector2D pos);

    void                onMove( Vector2D incre );

    void				update();

private:

    Camera();

    Camera(int mode);

private:

    static Camera* cameraInstance;

    Vector2D*	focus;

    int         mode = CAMERA_MODE_CENTER;

    Vector2D	position = Vector2D(HERO_INITIAL_POSITION_X, HERO_INITIAL_POSITION_Y);
};


#endif // CAMERA_H
