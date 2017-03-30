//
//  Scene.cpp
//  RoboNeko
//
//  Created by nsp on 29/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(SDL_Renderer* renderer)
{
  _renderer = renderer;
}

void Scene::Add(Robit *robit)
{
  _robits.push_back(robit);
}

void Scene::doEvent(int mouseX, int mouseY)
{
  // Just assume 2 robits for now
  auto p = _robits.at(0)->p;
  auto q = _robits.at(1)->p;
  SDL_Rect robitFirstRect = { p.x, p.y, 32, 32 };
  SDL_Rect robitSecondRect = { q.x, q.y, 32, 32 };
  if(SDL_HasIntersection(&robitFirstRect, &robitSecondRect)) {
    _robits.at(0)->doCollision();
    _robits.at(1)->doCollision();
  }
  
  for(auto& r : _robits) { // the & suffix means "reference to"
    r->doEvent(mouseX, mouseY);
  }
  Render();
}

void Scene::Render()
{
  
}
