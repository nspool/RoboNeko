//
//  Robit.hpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Robit_hpp
#define Robit_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Robit_hpp */

enum RobitState { Pursue, Stop, Wait, Sleep };

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* _renderer, SDL_Point p);
  SDL_Rect getBounds();
  void render(SDL_Point* target);
private:
  SDL_Renderer* _renderer = 0;
  SDL_Point _position;
  RobitState _state = Pursue;
  int _startTime;
  int _stopTime;
  bool _isStopped = false;
  bool _wasStopped = false;
  double _xDelta = 0;
  double _yDelta = 0;
  SDL_Rect _frame[6];
  SDL_Texture* _texture;
};
