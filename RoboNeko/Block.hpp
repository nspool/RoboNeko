//
//  Block.hpp
//  RoboNeko
//
//  Created by nsp on 1/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Block_hpp */

class Block : public Sprite
{
public:
  Block(SDL_Renderer* _renderer, SDL_Point p);
  void render();
  void stop();
  void doCollision(SDL_Rect*);
  bool isObsticle();
  SDL_Rect getBounds();
private:
  SDL_Point _p = {150, 150};
  SDL_Renderer* _renderer = 0;
  SDL_Rect spriteClips[1];
  SDL_Texture* mTexture;
};
