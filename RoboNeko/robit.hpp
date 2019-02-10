//
//  Robit.hpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright 2017 nspool. All rights reserved.
//

#ifndef Robit_hpp
#define Robit_hpp

#include <vector>

#include <SDL.h>
#include <SDL_timer.h>

#include "sprite.hpp"

const int ANIMATION_FPS = 10;
const int STATE_DELAY_MS = 1000;

enum RobitState : int { Pursue, Stop, Alert, Wait, Yawn, Sleep };

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* renderer, SDL_Point start_pos);
  void evaluate(SDL_Point* target);
  void render(SDL_Renderer* renderer);
private:
  RobitState state_;
  SDL_Rect position_;
  SDL_Texture* texture_;
  std::vector<SDL_Rect> frames_;
  unsigned int transition_tm_ = 0;
  void transition(RobitState newState);
};

#endif
