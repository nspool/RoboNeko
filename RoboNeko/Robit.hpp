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
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Robit_hpp */

enum RobitState { Pursue, Stop, Wait, Sleep };

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* _renderer, SDL_Point p);
  SDL_Rect getBounds();
//  void render();
//  void stop();
  void render(SDL_Point* target);
private:
  RobitState _state = RobitState::Pursue;
  bool _isCollided = false;
  int _lastTransition;
  int _startTime;
  int _stopTime;
  bool _isStopped = false;
  bool _wasStopped = false;

  
  SDL_Point _p = {0, 200};
  double _rad = M_PI_2;
  double _xDelta = 0;
  double _yDelta = 0;
  int _lastMouseX = 0;
  int _lastMouseY = 0;
  SDL_Renderer* _renderer = 0;
  SDL_Rect _spriteClips[6];
  SDL_Texture* _texture;
};
