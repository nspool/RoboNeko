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
  
  // Load the robit
  SDL_Surface* gRobits = IMG_Load( "robits.png" );
  
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
  
  _texture = SDL_CreateTextureFromSurface( renderer, gRobits );
}

void Robit::stop()
{
  SDL_Rect robitLoc = { _p.x, _p.y, 21, 31 };
  SDL_RenderCopy( _renderer, _texture, &_spriteClips[1], &robitLoc );
}

void Robit::doCollision()
{
  // "revert" to the previous uncollided position
  _p = _prev;
  _isCollided = true;
}


void Robit::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  
  if(_isCollided == true) {
    _isCollided = false;
    return;
  }
  
  bool willCollide = false;
  
  SDL_Rect P1 = { _p.x, _p.y };
  SDL_Rect P2 = { _p.x + 21, _p.y + 31 };
  SDL_Rect P3 = { _p.x, _p.y + 31 };
  SDL_Rect P4 = { _p.x + 21, _p.y };

  for(SDL_Rect o: *obsticles) {
    if(o.x == _p.x && o.y == _p.y) { continue; }
    // Modify the angle randomly to attempt to avoid collision.
    if(SDL_IntersectRectAndLine(&o, &P1.x, &P1.y, &target->x, &target->y) ||
       SDL_IntersectRectAndLine(&o, &P2.x, &P2.y, &target->x, &target->y) ||
       SDL_IntersectRectAndLine(&o, &P3.x, &P3.y, &target->x, &target->y) ||
       SDL_IntersectRectAndLine(&o, &P4.x, &P4.y, &target->x, &target->y)){
      willCollide = true;
      break;
    }
  }
  
  // Save the current position if the update position enters a collision sate
  _prev = _p;
  
  // Interpolate the line between the current position and the target
  SDL_Rect center = {_p.x + 10, _p.y + 15};
  double rad = atan2((target->y - center.y), (target->x - center.x));
  
  // TODO: Use obsticle obtains above to determine a path around
  if(willCollide) {
    rad += (arc4random_uniform(3) - 1.5);
  }
  
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
  // Animate at some fixed framerate
  constexpr int animationRate = 12;
  constexpr int animationLen = 3;
  int frameToDraw = ((SDL_GetTicks() - _startTime) * animationRate / 1000) % animationLen;
  SDL_Rect bounds = getBounds();
  SDL_RenderCopy( _renderer, _texture, &_spriteClips[frameToDraw], &bounds );
}
