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

TTF_Font *_font = 0;
SDL_Window* _window = 0;
SDL_Surface* _screenSurface = 0;
SDL_Surface* _background = 0;
SDL_Renderer* _renderer = 0;

int _startTime = SDL_GetTicks();
int mouseX = 0;
int mouseY = 0;



class Robit
{
public:
  static const int SPRITE_WIDTH = 32;
  static const int SPRITE_ANIMATION_LEN = 3;
  Robit();
  void doEvent();
  SDL_Point p = {0, 200};
private:
  double rad = M_PI_2;
  double xDelta = 0;
  double yDelta = 0;
  SDL_Rect spriteClips[3];
  int _animationRate = 12;
  SDL_Texture* gRobitsTexture;
};

Robit::Robit()
{
  // Load the robit
  SDL_Surface* gRobits = IMG_Load( "robits.png" );
//  SDL_Surface* gTextureImage = IMG_Load( "tex.png" );
  
  if(gRobits == 0) // || gTextureImage == 0)
  {
    printf( "Failed to load images! SDL_Error: %s\n", SDL_GetError() );
  }
  
  // Setup Robit animation
  spriteClips[0].x = 0;
  spriteClips[0].y = 0;
  spriteClips[0].w = 32;
  spriteClips[0].h = 32;
  
  spriteClips[1].x = 32;
  spriteClips[1].y = 0;
  spriteClips[1].w = 32;
  spriteClips[1].h = 32;
  
  spriteClips[2].x = 64;
  spriteClips[2].y = 0;
  spriteClips[2].w = 32;
  spriteClips[2].h = 32;
  
  gRobitsTexture = SDL_CreateTextureFromSurface( _renderer, gRobits );
  SDL_SetTextureColorMod( gRobitsTexture, 255, 25, 25 );
}

void Robit::doEvent()
{
  // Update |p| to new position
  rad = atan2((mouseY - p.y), (mouseX - p.x));
  xDelta += cos(rad);
  yDelta += sin(rad);
  
  if(xDelta > 1 || xDelta < -1){
    p.x += (int)xDelta;
    xDelta = 0;
  }
  
  if(yDelta > 1 || yDelta < -1){
    p.y += (int)yDelta;
    yDelta = 0;
  }
  
  // Bounds
  if(p.x < 0) { rad = 2 * M_PI; }
  if((p.x + SPRITE_WIDTH) > SCREEN_WIDTH) { rad = M_PI; }
  
  if(p.y < 0) { rad = M_PI_2; }
  if((p.y + SPRITE_WIDTH) > SCREEN_HEIGHT) { rad = -M_PI_2; }
  
  
  // Animate at some fixed framerate
  int frameToDraw = ((SDL_GetTicks() - _startTime) * _animationRate / 1000) % SPRITE_ANIMATION_LEN;
  SDL_Rect robitLoc = { p.x, p.y, 32, 32 };
  SDL_RenderCopy( _renderer, gRobitsTexture, &spriteClips[frameToDraw], &robitLoc );
}


SDL_Surface *load_image(std::string filename)
{
  SDL_Surface* loadedImage = 0;
  SDL_Surface* optimisedImage = 0;
  loadedImage = SDL_LoadBMP(filename.c_str());
  if(loadedImage != 0)
  {
    optimisedImage = SDL_ConvertSurface(loadedImage, _screenSurface->format, 0);
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
  _window = SDL_CreateWindow( "RoboNeko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  SDL_SetWindowTitle(_window, "RoboNeko");
  
  if( _window == 0 )
  {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  
  _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
  
  if( _renderer == 0 )
  {
    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    return 1;
  }
  
  //Initialize renderer color
  SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  

  // TODO: background texture
  //    SDL_Texture* gTexture = SDL_CreateTextureFromSurface( gRenderer, gTextureImage );

  

  
  bool quit = false;
  
  // event handler
  SDL_Event e;
  


  Robit* r1 = new Robit();
  Robit* r2 = new Robit();
  r2->p = {0, 100};
  
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
    
    // Clear window
    SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( _renderer );
    
    r1->doEvent();
    r2->doEvent();
    
    SDL_RenderPresent( _renderer );
    
  } while(!quit);
  
  //Destroy window
  SDL_DestroyWindow( _window );
  
  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}
