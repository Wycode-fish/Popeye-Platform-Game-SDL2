#ifndef MAINPROGRAM_H
#define MAINPROGRAM_H

#include <unistd.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "camera.h"
#include "tilemapsystem.h"
#include "ltexture.h"
#include "collisionsystem.h"
#include "displaysystem.h"
#include "playsystem.h"
#include "hero.h"
#include "ltimer.h"
#include "resourcemanager.h"
// This class represents the mainprogram
// Singleton design pattern
class MainProgram{
public:
    static MainProgram* getInstance();
    void run();

    ~MainProgram();
private:
    static MainProgram* gMainProgram;
    MainProgram();
    bool init();
    string getCurrentWorkingDirectory();
    void loop();
    float screenTickPerFrame = 1.0 / FPS;
};

#endif // MAINPROGRAM_H
