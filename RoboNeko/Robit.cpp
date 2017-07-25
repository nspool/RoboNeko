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
  _position = { initialPosition.x, initialPosition.y, 21, 31 };
  
  _renderer = renderer;
  
  SDL_Surface* gRobits  = SDL_CreateRGBSurfaceFrom((void*)robit_data.pixel_data,
                                                   robit_data.width,
                                                   robit_data.height,
                                                   32,
                                                   robit_data.bytes_per_pixel*robit_data.width,
                                                   0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
  
  if(gRobits == 0)
  {
    printf("Failed to load images! SDL_Error: %s\n", SDL_GetError());
    return;
  }
  
  for(int i=0; i<(robit_data.width/_position.w); i++) {
    SDL_Rect r = SDL_Rect();
    r.x =i*_position.w;
    r.h = 0;
    r.w = _position.w;
    r.h = robit_data.height;
    _frames.push_back(r);
  }
  
  _spriteSheet = SDL_CreateTextureFromSurface(renderer, gRobits);
  
  changeState(Pursue);
}

void Robit::changeState(RobitState newState) {
  if(newState == _state) { return; }
  _state = newState;
  _lastChangeTime = SDL_GetTicks();
}

void Robit::render(SDL_Point* target)
{
  bool intervalElapsed = ((SDL_GetTicks() - _lastChangeTime) > 1000);
  
  if(SDL_PointInRect(target, &_position)){
    if(_state == Pursue){
      changeState(Stop);
    }
  } else {
    if(_state == Sleep) {
      changeState(Alert);
    } else  if(_state == Yawn || _state == Wait) {
      changeState(Pursue);
    }
  }
  
  switch(_state){
    case Sleep:
      break;
    case Stop:
      if(intervalElapsed) {
        changeState(Wait);
      }
      break;
    case Wait:
      if(intervalElapsed) {
        changeState(Yawn);
      }
      break;
    case Yawn:
      if(intervalElapsed) {
        changeState(Sleep);
      }
      break;
    case Alert:
      if(intervalElapsed) {
        changeState(Pursue);
      }
      break;
    case Pursue:
      // Interpolate the line between the current position and the target
      SDL_Rect center = {_position.x + _position.w / 2, _position.y + _position.h / 2};
      double rad = atan2((target->y - center.y), (target->x - center.x));
      
      // Set the new coordinates
      _delta.x += cos(rad);
      _delta.y += sin(rad);
      
      if(_delta.x > 1 || _delta.x < -1){
        _position.x += (int)_delta.x;
        _delta.x = 0;
      }
      
      if(_delta.y > 1 || _delta.y < -1){
        _position.y += (int)_delta.y;
        _delta.y = 0;
      }
      break;
  }
  
  constexpr int animationRate = 12;

  int frameToDraw = 0;

  switch(_state){
    case Yawn:
      SDL_RenderCopy(_renderer, _spriteSheet, &_frames[8], &_position);
      break;
    case Sleep:
      frameToDraw = ((SDL_GetTicks() - _lastChangeTime) / 1000);
      SDL_RenderCopy(_renderer, _spriteSheet, &_frames[frameToDraw % 2 + 5], &_position);
      break;
    case Stop:
      SDL_RenderCopy(_renderer, _spriteSheet, &_frames[4], &_position);
      break;
    case Alert:
      SDL_RenderCopy(_renderer, _spriteSheet, &_frames[3], &_position);
      break;
    case Wait:
      SDL_RenderCopy(_renderer, _spriteSheet, &_frames[7], &_position);
      break;
    case Pursue:
      frameToDraw = ((SDL_GetTicks() - _lastChangeTime) * animationRate / 1000);
      SDL_RenderCopy( _renderer, _spriteSheet, &_frames[frameToDraw % 3], &_position);
      break;
  }
}
