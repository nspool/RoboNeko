//
//  Robit.hpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Robit_hpp
#define Robit_hpp

//#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Markov.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

#endif /* Robit_hpp */

class Robit
{
public:
  static const int SPRITE_WIDTH = 32;
  static const int SPRITE_ANIMATION_LEN = 3;
  Robit(SDL_Renderer* _renderer);
  void doEvent(int mouseX, int mouseY);
  void stop();
  SDL_Point p = {0, 200};
private:
  int currentTranceDirection = 0;
  int _lastTransition = SDL_GetTicks();
  int _startTime = SDL_GetTicks();
  double rad = M_PI_2;
  double xDelta = 0;
  double yDelta = 0;
  int oldMouseX = 0;
  int oldMouseY = 0;
  SDL_Renderer* renderer = 0;
  SDL_Rect spriteClips[3];
  int _animationRate = 12;
  SDL_Texture* gRobitsTexture;
  Markov* m;
};
