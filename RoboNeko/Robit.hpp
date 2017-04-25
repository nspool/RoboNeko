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
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

#endif /* Robit_hpp */

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* _renderer, SDL_Point p);
  void setGoal(SDL_Point* p);

  void render();
  void stop();
  void doCollision();
  SDL_Rect getBounds();
  
private:
  int _currentTranceDirection = 0;
  int _lastTransition;
  int _startTime;
  SDL_Point _p = {0, 200};
  double _rad = M_PI_2;
  double _xDelta = 0;
  double _yDelta = 0;
  int _lastMouseX = 0;
  int _lastMouseY = 0;
  SDL_Renderer* _renderer = 0;
  SDL_Rect _spriteClips[3];
  SDL_Texture* _texture;
};
