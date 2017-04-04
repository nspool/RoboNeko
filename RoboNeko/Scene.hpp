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


#include "Robit.hpp"
#include "Block.hpp"

class Scene
{
public:
  Scene(SDL_Renderer* _renderer);
  void Add(Robit* robit);
  void Render();
  void doEvent(int mouseX, int mouseY);
private:
  SDL_Renderer* _renderer;
  std::vector<Robit*> _robits;
  Block* block;
};
