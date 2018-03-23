//
//  LTexture.h
//  BreakoutGame
//
//  Created by Tianxiang Dai on 1/30/18.
//  Copyright © 2018 Tianxiang Dai. All rights reserved.
//

#ifndef LTexture_h
#define LTexture_h

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "constants.h"
#include <iostream>


using namespace std;
/**
 * @brief This class is the texture wrapper.
 */
class LTexture {
public:
    /**
     * @brief Initializes variables
     */
    LTexture();

    /**
     * @brief Deallocates memory
     */
    ~LTexture();

    /**
     * @brief Loads image from specified path
     *
     * @param path The path of the image file
     * @param gRenderer the renderer to render the texture
     */
    bool loadFromFile( std::string path, SDL_Renderer* gRenderer = NULL );

    /**
     * @brief Creates image from font string
     *
     * @param textureText the text to be converted
     * @param textColor the color of the text
     * @param gFont the font of the text
     * @param gRenderer the renderer to render the text
     *
     * @returns true if succeeds
     */
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor , TTF_Font* gFont = NULL , SDL_Renderer* gRenderer = NULL );

    /**
     * @brief Deallocates texture
     */
    void free();

    /**
     * @brief Set color modulation
     */
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    /**
     * @brief Set blending
     */
    void setBlendMode( SDL_BlendMode blending );

    /**
     * @brief Set alpha modulation
     */
    void setAlpha( Uint8 alpha );

    /**
     * @brief Render texture at given point
     *
     * @param x x position of the point
     * @param y y position of the point
     * @param gRenderer the renderer to render the texture
     * @param clip
     * @param angle
     * @param center
     * @param flip
     */
    void render( int x, int y, SDL_Renderer* gRenderer = NULL, SDL_Rect* clip = NULL, SDL_Rect* shrink = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void render( SDL_Renderer* gRenderer, string nameTag, bool isCol, int X, int Y, int X2, int Y2, int W, int H);

    void renderWith();
    /**
     * @brief Get texture
     */
    SDL_Texture* getTexture();

    /**
     * @brief Get the width of image
     */
    int getWidth();
    /**
     * @brief Get the height of the image
     */
    int getHeight();

public:

    void renderStatic (SDL_Renderer* gRenderer, int X, int Y, int W1, int H1, int X2, int Y2, int W2, int H2);



private:
    SDL_Texture* mTexture; /**< The actual hardware texture */

    int mWidth; /**< The width of image */
    int mHeight; /**< The height of image */
};

#endif /* LTexture_h */

