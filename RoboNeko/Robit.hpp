//
//  Robit.hpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Robit_hpp
#define Robit_hpp

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Robit_hpp */

enum RobitState : int { Pursue, Stop, Alert, Wait, Yawn, Sleep };

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* _renderer, SDL_Point p);
  void render(SDL_Point* target);
private:
  std::vector<SDL_Rect> _frames;
  SDL_Renderer* _renderer;
  SDL_Texture* _spriteSheet;
  RobitState _state;
  SDL_Rect _position;
  unsigned int _lastChangeTime = 0;
  void changeState(RobitState newState);
};
