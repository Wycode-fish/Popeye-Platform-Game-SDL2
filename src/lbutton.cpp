#include "../include/lbutton.h"

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;

    click = false;

    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

LButton::~LButton(){
    // Now do nothing
}

void LButton::setPosition( int x, int y )
{
    mPosition.x = x;
    mPosition.y = y;
}

LButtonSprite LButton::getCurrentSprite(){
    return mCurrentSprite;
}


void LButton::handleEvent( SDL_Event* e )
{
    //If mouse event happened
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );

        //Check if mouse is in button
        bool inside = true;

        //Mouse is left of the button
        if( x < mPosition.x )
        {
            inside = false;
        }
        //Mouse is right of the button
        else if( x > mPosition.x + BUTTON_WIDTH )
        {
            inside = false;
        }
        //Mouse above the button
        else if( y < mPosition.y )
        {
            inside = false;
        }
        //Mouse below the button
        else if( y > mPosition.y + BUTTON_HEIGHT )
        {
            inside = false;
        }

        //Mouse is outside button
        if( !inside )
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
            click = false;
        }
        //Mouse is inside button
        else
        {
            //Set mouse over sprite
            switch( e->type )
            {
            case SDL_MOUSEMOTION:{
                click = false;
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            }

            case SDL_MOUSEBUTTONDOWN:{
                click = false;
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            }

            case SDL_MOUSEBUTTONUP:{
                click = true;
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
            }
        }
    } else {
        click = false;
    }
}

void LButton::render( LTexture* gButtonSpriteSheetTexture, SDL_Renderer* renderer, SDL_Rect clip )
{
    //Show current button sprite
    SDL_Rect buttonSize;
    buttonSize.x = 0;
    buttonSize.y = 0;
    buttonSize.w = BUTTON_WIDTH;
    buttonSize.h = BUTTON_HEIGHT;
    gButtonSpriteSheetTexture->render( mPosition.x, mPosition.y, renderer, &clip, &buttonSize );
}

void LButton::setCurrentSprite( LButtonSprite sprite ){
    this->mCurrentSprite = sprite;
}

bool LButton::isClick(){
    return click;
}
