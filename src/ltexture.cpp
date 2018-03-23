#include "../include/ltexture.h"

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer* gRenderer )
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }

    //Return success
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* gFont , SDL_Renderer* gRenderer )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Return success
    return mTexture != NULL;
}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_Rect* shrink, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    cout << "Width : " << mWidth << " Height : " << mHeight << endl;

    if (!mTexture)
        cout << "Texture is Null!\n";

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    if ( shrink != NULL ){
        renderQuad.w = shrink->w;
        renderQuad.h = shrink->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}



void LTexture::render (SDL_Renderer* gRenderer, string nameTag, bool isCol, int X, int Y, int X2, int Y2, int W, int H) {


    // switch(nameTag) {
    //     case "Hero":
    //         renderHero();
    //     case "Minioin":
    //     case "PowerUp":
    //     case "Bullet":

    //     default:
    //         cout<< "No Expected NameTag for Render."<<endl;
    // }

    int frameHeight = (nameTag=="Hero")?HERO_FRAME_HEIGHT:MINION_FRAME_HEIGHT;

    SDL_Rect DestR;
    DestR.x = X;
    DestR.y = Y;

    SDL_Rect SrcR;
    SrcR.x = X2;
    SrcR.y = (isCol && nameTag=="Hero")?Y2+HERO_POSE_COUNT:Y2;
    SrcR.w = W;
    SrcR.h = H;

    cout<<"\n#############. Render Dynamic: ################"<<endl;
    cout<<"Name:"+nameTag+",  X:"+to_string(X)+", Y"+to_string(Y)+", X2:"+to_string(X2)+", Y2:"+to_string(Y2)+", W:"+to_string(W)+", H:"+to_string(H)+"\n"<<endl;
    SDL_RenderCopyEx (gRenderer, mTexture, &SrcR, &DestR, 0, NULL, SDL_FLIP_NONE);
}


void LTexture::renderStatic (SDL_Renderer* gRenderer, int X, int Y, int W1, int H1, int X2, int Y2, int W2, int H2) {

    SDL_Rect DestR;
    DestR.x = X;
    DestR.y = Y;
    DestR.w = W1;
    DestR.h = H1;

    SDL_Rect SrcR;
    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W2;
    SrcR.h = H2;

    SDL_RenderCopy (gRenderer, mTexture, &SrcR, &DestR);
}



int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

//Get texture
SDL_Texture* LTexture::getTexture(){
    return mTexture;
}

