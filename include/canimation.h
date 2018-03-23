#ifndef CANIMATION_H
#define CANIMATION_H


#include <iostream>
#include "vector2d.h"
#include "constants.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class CAnimation {
    private:
        int     currentFrame;

        int     frameInc;

    private:
        int     frameRate; //Milliseconds

        long    oldTime;

    public:
        int     maxFrames;

        bool    oscillate;

    public:
        CAnimation();

        void onAnimate();

    public:

        void setFrameRate(int rate);

        void setCurrentFrame(int frame);

        int getCurrentFrame();

        void setMaxFrames(int max);
};


#endif // CANIMATION_H
