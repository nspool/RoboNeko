//
//  Scene.hpp
//  RoboNeko
//
//  Created by nsp on 29/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#endif /* Scene_hpp */

#include "Sprite.hpp"

class Scene
{
public:
  Scene(SDL_Renderer* _renderer);
  void Add(Sprite* sprite);
  void Render();
  void doEvent(SDL_Point* p);
private:
  SDL_Renderer* _renderer;
  std::vector<Sprite*> _sprites;
};
