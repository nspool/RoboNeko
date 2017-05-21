//
//  Robit.cpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Robit.hpp"

Robit::Robit(SDL_Renderer* renderer, SDL_Point p)
{
  
  _p = p;
  _renderer = renderer;
  
  SDL_Surface* gRobits = IMG_Load("robits.png");
  
  if(gRobits == 0)
  {
    printf("Failed to load images! SDL_Error: %s\n", SDL_GetError());
  }
  
  // Setup Robit animation
  _spriteClips[0].x = 0;
  _spriteClips[0].y = 0;
  _spriteClips[0].w = 21;
  _spriteClips[0].h = 31;
  
  _spriteClips[1].x = 21;
  _spriteClips[1].y = 0;
  _spriteClips[1].w = 21;
  _spriteClips[1].h = 31;
  
  _spriteClips[2].x = 42;
  _spriteClips[2].y = 0;
  _spriteClips[2].w = 21;
  _spriteClips[2].h = 31;
  
  _spriteClips[3].x = 63;
  _spriteClips[3].y = 0;
  _spriteClips[3].w = 21;
  _spriteClips[3].h = 31;

  _spriteClips[4].x = 84;
  _spriteClips[4].y = 0;
  _spriteClips[4].w = 21;
  _spriteClips[4].h = 31;
  
  _spriteClips[5].x = 105;
  _spriteClips[5].y = 0;
  _spriteClips[5].w = 21;
  _spriteClips[5].h = 31;
  
  _texture = SDL_CreateTextureFromSurface(renderer, gRobits);
  
}

void Robit::stop()
{
  _isStopped = true;
  _stopTime = SDL_GetTicks();
}

void Robit::action(SDL_Point* target)
{
  // TODO: Replace with a switch around the RobitState
  if(_isStopped) {
    SDL_Rect bounds = getBounds();
    if(SDL_PointInRect(target, &bounds)) {
      _stopTime = SDL_GetTicks();
      return;
    }
    if( (SDL_GetTicks() - _stopTime) > 1000 ) {
      _isStopped = false;
      _wasStopped = true;
      _stopTime = SDL_GetTicks();
    } else {
      return;
    }
  }
  
  if(_wasStopped) {
    if( (SDL_GetTicks() - _stopTime) > 1000 ) {
      _isStopped = false;
      _wasStopped = false;
    } else {
      return;
    }
  }
  
  SDL_Rect bounds = getBounds();
  if(SDL_PointInRect(target, &bounds)){
    stop();
    return;
  }
  
  int width = 21;
  int height = 31;
  
  // Interpolate the line between the current position and the target
  SDL_Rect center = {_p.x + width / 2, _p.y + height / 2};
  double rad = atan2((target->y - center.y), (target->x - center.x));
  
  // Set the new coordinates
  _xDelta += cos(rad);
  _yDelta += sin(rad);
  
  if(_xDelta > 1 || _xDelta < -1){
    _p.x += (int)_xDelta;
    _xDelta = 0;
  }
  
  if(_yDelta > 1 || _yDelta < -1){
    _p.y += (int)_yDelta;
    _yDelta = 0;
  }
}

SDL_Rect Robit::getBounds()
{
  return { _p.x, _p.y, 21, 31 };
}

void Robit::render()
{
  SDL_Rect bounds = getBounds();
  if(_isStopped) {
    SDL_RenderCopy(_renderer, _texture, &_spriteClips[5], &bounds);
  } else if(_wasStopped) {
    SDL_RenderCopy(_renderer, _texture, &_spriteClips[3], &bounds);
  }else {
    // Animate at some fixed framerate
    constexpr int animationRate = 12;
    constexpr int animationLen = 3;
    int frameToDraw = ((SDL_GetTicks() - _startTime) * animationRate / 1000) % animationLen;
    SDL_RenderCopy( _renderer, _texture, &_spriteClips[frameToDraw], &bounds );
  }
}
