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

#include "Markov.hpp"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

#endif /* Robit_hpp */

class Robit
{
public:
  Robit(SDL_Renderer* _renderer);
  void doEvent(int mouseX, int mouseY);
  void stop();
  SDL_Point p = {0, 200};
private:
  int currentTranceDirection = 0;
  int _lastTransition;
  int _startTime;
  double rad = M_PI_2;
  double xDelta = 0;
  double yDelta = 0;
  int mLastMouseX = 0;
  int mLastMouseY = 0;
  SDL_Renderer* _renderer = 0;
  SDL_Rect spriteClips[3];
  SDL_Texture* mTexture;
  Markov* m;
};
