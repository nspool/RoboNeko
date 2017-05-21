//
//  Sprite.hpp
//  RoboNeko
//
//  Created by nsp on 25/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <SDL2/SDL.h>

struct Sprite
{
public:
  virtual void render(SDL_Point* target) {}
};

#endif /* Sprite_hpp */
