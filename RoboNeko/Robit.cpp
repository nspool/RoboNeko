//
//  Robit.cpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Robit.hpp"

Robit::Robit(SDL_Renderer* renderer)
{
  
  _renderer = renderer;
  
  // Load the robit
  SDL_Surface* gRobits = IMG_Load( "robits.png" );
  
  if(gRobits == 0)
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
  
  mTexture = SDL_CreateTextureFromSurface( renderer, gRobits );
}

void Robit::stop()
{
  SDL_Rect robitLoc = { p.x, p.y, 32, 32 };
  SDL_RenderCopy( _renderer, mTexture, &spriteClips[1], &robitLoc );
}

void Robit::doCollision()
{
  // Just try a different direction
  currentTranceDirection = m->GetNextState();
}

// Should return: next state
void Robit::doEvent(int mouseX, int mouseY)
{
  
  constexpr int width = 32;
  constexpr int animationLen = 3;
  
  if(mLastMouseX == mouseX && mLastMouseY == mouseY) {

    if((SDL_GetTicks() > (_lastTransition + 1000))){
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
      case 4:
        rad = -M_PI_2;
        break;
      default:
        stop();
        return;
        break;
    }
  } else {    
    rad = atan2((mouseY - p.y), (mouseX - p.x));
  }
  
  mLastMouseY = mouseY;
  mLastMouseX = mouseX;
  
  // Bounds
  if(p.x < 0) { currentTranceDirection = 2; rad = 2 * M_PI; }
  if((p.x + width) > SCREEN_WIDTH) { currentTranceDirection = 0; rad = M_PI; }
  
  if(p.y < 0) { currentTranceDirection = 3; rad = M_PI_2; }
  if((p.y + width) > SCREEN_HEIGHT) { currentTranceDirection = 4; rad = -M_PI_2; }
  
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
  constexpr int animationRate = 12;
  int frameToDraw = ((SDL_GetTicks() - _startTime) * animationRate / 1000) % animationLen;
  SDL_Rect robitLoc = { p.x, p.y, 32, 32 };
  SDL_RenderCopy( _renderer, mTexture, &spriteClips[frameToDraw], &robitLoc );
}
