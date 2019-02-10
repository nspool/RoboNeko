//
//  Sprite.hpp
//  RoboNeko
//
//  Created by nsp on 25/4/17.
//  Copyright 2017 nspool. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL.h>

struct Sprite
{
public:
  virtual void evaluate(SDL_Point* target) = 0;
  virtual void render(SDL_Renderer* renderer) = 0;
};

#endif
