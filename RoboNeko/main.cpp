//
//  main.cpp
//  RoboNeko
//
//  Created by nspool on 8/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include <iostream>

#include <math.h>

#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SPRITE_WIDTH = 32;
const int SPRITE_ANIMATION_LEN = 3;

TTF_Font *mFont = 0;
SDL_Window* mWindow = 0;
SDL_Surface* mScreenSurface = 0;
SDL_Surface* mBackground = 0;
SDL_Renderer* mRenderer = 0;
SDL_Rect mSpriteClips[ 3 ];

int mAnimationRate = 12;
int mStartTime = SDL_GetTicks();

SDL_Surface *load_image(std::string filename)
{
  SDL_Surface* loadedImage = 0;
  SDL_Surface* optimisedImage = 0;
  loadedImage = SDL_LoadBMP(filename.c_str());
  if(loadedImage != 0)
  {
    optimisedImage = SDL_ConvertSurface(loadedImage, mScreenSurface->format, 0);
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
  
  if( mWindow == 0 )
  {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  
  mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
  
  if( mRenderer == 0 )
  {
    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    return 1;
  }
  
  //Initialize renderer color
  SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
  
  // Load the robit
  SDL_Surface* gRobits = IMG_Load( "robits.png" );
  SDL_Surface* gTextureImage = IMG_Load( "tex.png" );
  
  if(gRobits == 0 || gTextureImage == 0)
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
  
  SDL_Point p = {0, 200};
  double rad = M_PI_2;
  
  int mouseX = 0;
  int mouseY = 0;
  double xDelta = 0, yDelta = 0;
  
  // Main event loop
  
  do {
    while(SDL_PollEvent(&e) != 0)
    {
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
        case SDL_MOUSEMOTION:
          SDL_GetMouseState( &mouseX, &mouseY );
        default:
          break;
      }
    }
    

    rad = atan2((mouseY - p.y), (mouseX - p.x));
    
    // Update |p| to new position
    xDelta += cos(rad);
    yDelta += sin(rad);
    if(xDelta > 1){
      p.x += 1;
      xDelta = 0;
    }
    if(yDelta > 1){
      p.y += 1;
      yDelta = 0;
    }
    if(xDelta < -1){
      p.x -= 1;
      xDelta = 0;
    }
    if(yDelta < -1){
      p.y -= 1;
      yDelta = 0;
    }
    printf("%f %f\n", xDelta, yDelta);
    // Bounds
    if(p.x < 0) { rad = 2 * M_PI; }
    if((p.x + SPRITE_WIDTH) > SCREEN_WIDTH) { rad = M_PI; }
    
    if(p.y < 0) { rad = M_PI_2; }
    if((p.y + SPRITE_WIDTH) > SCREEN_HEIGHT) { rad = -M_PI_2; }
    
    // Clear window
    SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( mRenderer );
    
    // Animate at some fixed framerate
    int frameToDraw = ((SDL_GetTicks() - mStartTime) * mAnimationRate / 1000) % SPRITE_ANIMATION_LEN;
    SDL_Rect robitLoc = { p.x, p.y, 32, 32 };
    SDL_RenderCopy( mRenderer, gRobitsTexture, &mSpriteClips[frameToDraw], &robitLoc );
    SDL_RenderPresent( mRenderer );
    
  } while(!quit);
  
  //Destroy window
  SDL_DestroyWindow( mWindow );
  
  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}
