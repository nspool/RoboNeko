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

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

TTF_Font *gFont = NULL;
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* gBackground = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Rect gSpriteClips[ 3 ];

SDL_Surface *load_image(std::string filename)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimisedImage = NULL;
    loadedImage = SDL_LoadBMP(filename.c_str());
    if(loadedImage != NULL)
    {
        optimisedImage = SDL_ConvertSurface(loadedImage, screenSurface->format, NULL);
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
    window = SDL_CreateWindow( "RoboNeko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_SetWindowTitle(window, "RoboNeko");
    
    if( window == NULL )
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    
    if( gRenderer == NULL )
    {
        printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    //Initialize renderer color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    // Load the robit
    SDL_Surface* gRobits = IMG_Load( "robits.png" );
    SDL_Surface* gTextureImage = IMG_Load( "tex.png" );
    
    if(gRobits == NULL || gTextureImage == NULL)
    {
        printf( "Failed to load images! SDL_Error: %s\n", SDL_GetError() );
        return 1;
    }
    
    SDL_Texture* gTexture = SDL_CreateTextureFromSurface( gRenderer, gTextureImage );
    SDL_Texture* gRobitsTexture = SDL_CreateTextureFromSurface( gRenderer, gRobits );
    SDL_SetTextureColorMod( gRobitsTexture, 255, 25, 25 );
    
    // Just to make sure that the window is created..
    SDL_Delay( 2000 );
    
    //Destroy window
    SDL_DestroyWindow( window );
    
    //Quit SDL subsystems
    SDL_Quit();
    
    return 0;
}
