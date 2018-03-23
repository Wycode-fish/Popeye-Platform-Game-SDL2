#include "../include/canimation.h"

CAnimation::CAnimation() {
    currentFrame 	= 0;
    frameInc		= 1;
    maxFrames		= 0;

    oldTime			= 0;
    frameRate 		= FPS;

    oscillate		= false;
}

void CAnimation::onAnimate() {

    if(oldTime + frameRate > SDL_GetTicks()) {
        cout<<"CAnimation: onAnimate() currentFrame not change."<<endl;
        return;
    }

    oldTime = SDL_GetTicks();

    currentFrame += frameInc;

    if(oscillate) {
        if(frameInc > 0) {
            if(currentFrame >= maxFrames) {
                frameInc = -frameInc;
            }
        }
        else{
            if(currentFrame <= 0) {
                frameInc = -frameInc;
            }
        }
    }

    else{
        if(currentFrame >= maxFrames) {
            currentFrame = 0;
        }
    }
}


void CAnimation::setFrameRate(int rate) {
    frameRate = rate;
}

void CAnimation::setMaxFrames(int max) {
    maxFrames = max;
}

void CAnimation::setCurrentFrame(int frame) {
    if (frame < 0 || frame > maxFrames) {
        cout<<"CAnimation: setCurrentFrame() failed."<<endl;
        return;
    }
    currentFrame = frame;
}

int CAnimation::getCurrentFrame() {
    return currentFrame;
}
