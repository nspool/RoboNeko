//
//  Robit.cpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Robit.hpp"

Robit::Robit(SDL_Renderer* _renderer)
{
  renderer = _renderer;
  
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
  
  gRobitsTexture = SDL_CreateTextureFromSurface( renderer, gRobits );
  SDL_SetTextureColorMod( gRobitsTexture, 255, 25, 25 );
}

void Robit::stop()
{
  SDL_Rect robitLoc = { p.x, p.y, 32, 32 };
  SDL_RenderCopy( renderer, gRobitsTexture, &spriteClips[1], &robitLoc );
}

void Robit::doEvent(int mouseX, int mouseY)
{
  
  if(oldMouseX == mouseX && oldMouseY == mouseY) {
    //    stop();
    if((SDL_GetTicks() > (_lastTransition + 1000))){
      // Get a new direction
      _lastTransition = SDL_GetTicks();
      currentTranceDirection = m->GetNextState();
    }
    
    switch (currentTranceDirection) {
      case 0:
        rad = M_PI;
        break;
      case 1:
        rad = -M_PI;
        break;
      case 2:
        rad = 2 * M_PI;
        break;
      case 3:
        rad = M_PI_2;
        break;
      default:
        stop();
        return;
        break;
    }
  } else {
    
    // Update |p| to new position
    rad = atan2((mouseY - p.y), (mouseX - p.x));
  }
  
  oldMouseY = mouseY;
  oldMouseX = mouseX;
  
  // Bounds
  if(p.x < 0) { rad = 2 * M_PI; }
  if((p.x + SPRITE_WIDTH) > SCREEN_WIDTH) { rad = M_PI; }
  
  if(p.y < 0) { rad = M_PI_2; }
  if((p.y + SPRITE_WIDTH) > SCREEN_HEIGHT) { rad = -M_PI_2; }
  
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
  
  // Animate at some fixed framerate
  int frameToDraw = ((SDL_GetTicks() - _startTime) * _animationRate / 1000) % SPRITE_ANIMATION_LEN;
  SDL_Rect robitLoc = { p.x, p.y, 32, 32 };
  SDL_RenderCopy( renderer, gRobitsTexture, &spriteClips[frameToDraw], &robitLoc );
}
