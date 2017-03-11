//
//  main.cpp
//  RoboNeko
//
//  Created by nspool on 8/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include <iostream>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPRITE_WIDTH = 32;
const int SPRITE_ANIMATION_LEN = 3;

TTF_Font *mFont = NULL;
SDL_Window* mWindow = NULL;
SDL_Surface* mScreenSurface = NULL;
SDL_Surface* mBackground = NULL;
SDL_Renderer* mRenderer = NULL;
SDL_Rect mSpriteClips[ 3 ];

int mAnimationRate = 12;
int mStartTime = SDL_GetTicks();

SDL_Surface *load_image(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimisedImage = NULL;
    loadedImage = SDL_LoadBMP(filename.c_str());
    if(loadedImage != NULL)
    {
        optimisedImage = SDL_ConvertSurface(loadedImage, mScreenSurface->format, NULL);
    }
    SDL_FreeSurface(loadedImage);
    return optimisedImage;
}

int main(int argc, const char * argv[]) {
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0 )
    {
        std::cout << "Failed to initialise SDL!" << std::endl;
        return 1;
    }
    
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        std::cout << "Failed to initialise SDL_image!" << std::endl;
        return 1;
    }
    
    //Create window
    mWindow = SDL_CreateWindow( "RoboNeko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_SetWindowTitle(mWindow, "RoboNeko");
    
    if( mWindow == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    
    if( mRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    //Initialize renderer color
    SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    // Load the robit
    SDL_Surface* gRobits = IMG_Load( "robits.png" );
    SDL_Surface* gTextureImage = IMG_Load( "tex.png" );
    
    if(gRobits == NULL || gTextureImage == NULL)
    {
        printf( "Failed to load images! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    // TODO: background texture
//    SDL_Texture* gTexture = SDL_CreateTextureFromSurface( gRenderer, gTextureImage );
    SDL_Texture* gRobitsTexture = SDL_CreateTextureFromSurface( mRenderer, gRobits );
    SDL_SetTextureColorMod( gRobitsTexture, 255, 25, 25 );
    
    // Setup Robit animation
    mSpriteClips[ 0 ].x =   0;
    mSpriteClips[ 0 ].y =   0;
    mSpriteClips[ 0 ].w =  32;
    mSpriteClips[ 0 ].h = 32;
    
    mSpriteClips[ 1 ].x =  32;
    mSpriteClips[ 1 ].y =  0;
    mSpriteClips[ 1 ].w =  32;
    mSpriteClips[ 1 ].h = 32;
    
    mSpriteClips[ 2 ].x = 64;
    mSpriteClips[ 2 ].y =   0;
    mSpriteClips[ 2 ].w =  32;
    mSpriteClips[ 2 ].h = 32;
    
    bool quit = false;
    
    // event handler
    SDL_Event e;
    int x = 0;
    
    // TODO: needs to be a vector
    int v = 1;
    
    // Main event loop
    
    do {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
        
        // Calculate new position
        if(x > SCREEN_WIDTH - SPRITE_WIDTH) { v = -1; }
        if(x < 0) { v = 1; }
        
        x += v;
        
        SDL_Rect robitLoc = { x, 200, 32, 32 };

        // Clear window
        SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( mRenderer );

        // Animate at some fixed framerate
        int frameToDraw = ((SDL_GetTicks() - mStartTime) * mAnimationRate / 1000) % SPRITE_ANIMATION_LEN;
        SDL_RenderCopy( mRenderer, gRobitsTexture, &mSpriteClips[frameToDraw], &robitLoc );
        SDL_RenderPresent( mRenderer );
        
    } while(!quit);
    
    //Destroy window
    SDL_DestroyWindow( mWindow );
    
    //Quit SDL subsystems
    SDL_Quit();
    
    return 0;
}
