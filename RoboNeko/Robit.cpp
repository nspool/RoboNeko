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
  
  constexpr int sprite_width = 21;
  for(int i=0; i<(robit_data.width/sprite_width); i++) {
    SDL_Rect r = SDL_Rect();
    r.x =i*sprite_width;
    r.h = 0;
    r.w = sprite_width;
    r.h = robit_data.height;
    _frames.push_back(r);
  }
    
  _spriteSheet = SDL_CreateTextureFromSurface(renderer, gRobits);
  
  changeState(Pursue);
}

void Robit::changeState(RobitState newState) {
  _state = newState;
  _lastChangeTime = SDL_GetTicks();
}

void Robit::render(SDL_Point* target)
{
  // TODO: Replace with a switch around the RobitState
  if(_state == Stop) {
    SDL_Rect bounds = getBounds();
    if(SDL_PointInRect(target, &bounds)) {
      _lastChangeTime = SDL_GetTicks();
    }
    if( (SDL_GetTicks() - _lastChangeTime) > 1000 ) {
      changeState(Wait);
      _lastChangeTime = SDL_GetTicks();
    }
  }
  
  if(_state == Wait) {
    if( (SDL_GetTicks() - _lastChangeTime) > 1000 ) {
      changeState(Pursue);
    }
  }
  
  SDL_Rect bounds = getBounds();
  if(SDL_PointInRect(target, &bounds)){
    changeState(Stop);
  }
  
  if(!(_state == Stop) && !(_state == Wait)) {
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
  
  if(_state == Stop) {
    SDL_RenderCopy(_renderer, _spriteSheet, &_frames[5], &bounds);
  } else if(_state == Wait) {
    SDL_RenderCopy(_renderer, _spriteSheet, &_frames[3], &bounds);
  }else {
    // Animate at some fixed framerate
    constexpr int animationRate = 12;
    constexpr int animationLen = 3;
    int frameToDraw = ((SDL_GetTicks() - _lastChangeTime) * animationRate / 1000) % animationLen;
    SDL_RenderCopy( _renderer, _spriteSheet, &_frames[frameToDraw], &bounds);
  }
}

SDL_Rect Robit::getBounds()
{
  return { _position.x, _position.y, 21, 31 };
}


