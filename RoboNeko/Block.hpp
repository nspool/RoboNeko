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

#endif /* Block_hpp */

class Block
{
public:
  Block(SDL_Renderer* _renderer);
  void render();
  void stop();
  void doCollision();
  SDL_Point p = {150, 150};
private:
  SDL_Renderer* _renderer = 0;
  SDL_Rect spriteClips[1];
  SDL_Texture* mTexture;
};
