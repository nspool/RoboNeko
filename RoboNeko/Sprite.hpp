//
//  Sprite.hpp
//  RoboNeko
//
//  Created by nsp on 25/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <vector>
#include <SDL2/SDL.h>

struct Sprite
{
public:
  virtual void render() {}
  virtual void stop() {}
  virtual void doCollision() {}
  virtual void action(SDL_Point* mouse) {};
  virtual SDL_Rect getBounds() { return SDL_Rect(); }
};

#endif /* Sprite_hpp */
