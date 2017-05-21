//
//  Robit.cpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Robit.hpp"

#include "robits.h"

Robit::Robit(SDL_Renderer* renderer, SDL_Point initialPosition)
{
  _position = initialPosition;
  _renderer = renderer;
  
  SDL_Surface* gRobits;
  Uint32 rmask, gmask, bmask, amask;
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
  gRobits = SDL_CreateRGBSurfaceFrom((void*)robit_data.pixel_data, robit_data.width, robit_data.height, 32, robit_data.bytes_per_pixel*robit_data.width, rmask, gmask, bmask, amask);
  
  if(gRobits == 0)
  {
    printf("Failed to load images! SDL_Error: %s\n", SDL_GetError());
  }
  
  // Setup Robit animation
  _frame[0].x = 0;
  _frame[0].y = 0;
  _frame[0].w = 21;
  _frame[0].h = 31;
  
  _frame[1].x = 21;
  _frame[1].y = 0;
  _frame[1].w = 21;
  _frame[1].h = 31;
  
  _frame[2].x = 42;
  _frame[2].y = 0;
  _frame[2].w = 21;
  _frame[2].h = 31;
  
  _frame[3].x = 63;
  _frame[3].y = 0;
  _frame[3].w = 21;
  _frame[3].h = 31;

  _frame[4].x = 84;
  _frame[4].y = 0;
  _frame[4].w = 21;
  _frame[4].h = 31;
  
  _frame[5].x = 105;
  _frame[5].y = 0;
  _frame[5].w = 21;
  _frame[5].h = 31;
  
  _texture = SDL_CreateTextureFromSurface(renderer, gRobits);
  
}

void Robit::render(SDL_Point* target)
{
  // TODO: Replace with a switch around the RobitState
  if(_isStopped) {
    SDL_Rect bounds = getBounds();
    if(SDL_PointInRect(target, &bounds)) {
      _stopTime = SDL_GetTicks();
    }
    if( (SDL_GetTicks() - _stopTime) > 1000 ) {
      _isStopped = false;
      _wasStopped = true;
      _stopTime = SDL_GetTicks();
    }
  }
  
  if(_wasStopped) {
    if( (SDL_GetTicks() - _stopTime) > 1000 ) {
      _isStopped = false;
      _wasStopped = false;
    }
  }
  
  SDL_Rect bounds = getBounds();
  if(SDL_PointInRect(target, &bounds)){
    _isStopped = true;
    _stopTime = SDL_GetTicks();
  }
  
  if(!_isStopped && !_wasStopped) {
    int width = 21;
    int height = 31;
    
    // Interpolate the line between the current position and the target
    SDL_Rect center = {_position.x + width / 2, _position.y + height / 2};
    double rad = atan2((target->y - center.y), (target->x - center.x));
    
    // Set the new coordinates
    _xDelta += cos(rad);
    _yDelta += sin(rad);
    
    if(_xDelta > 1 || _xDelta < -1){
      _position.x += (int)_xDelta;
      _xDelta = 0;
    }
    
    if(_yDelta > 1 || _yDelta < -1){
      _position.y += (int)_yDelta;
      _yDelta = 0;
    }
  }
  
  bounds = getBounds();
  
  if(_isStopped) {
    SDL_RenderCopy(_renderer, _texture, &_frame[5], &bounds);
  } else if(_wasStopped) {
    SDL_RenderCopy(_renderer, _texture, &_frame[3], &bounds);
  }else {
    // Animate at some fixed framerate
    constexpr int animationRate = 12;
    constexpr int animationLen = 3;
    int frameToDraw = ((SDL_GetTicks() - _startTime) * animationRate / 1000) % animationLen;
    SDL_RenderCopy( _renderer, _texture, &_frame[frameToDraw], &bounds);
  }
}

SDL_Rect Robit::getBounds()
{
  return { _position.x, _position.y, 21, 31 };
}


