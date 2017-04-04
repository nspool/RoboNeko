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
  block = new Block(renderer);
}

void Scene::Add(Robit *robit)
{
  _robits.push_back(robit);
}

void Scene::doEvent(int mouseX, int mouseY)
{
  
  // should really have a set of current positions allow each item
  // To determine its own next position, then given back to this class
  // Which will render it.
  
  // Just assume 2 robits for now
  auto p = _robits.at(0)->p;
  auto q = _robits.at(1)->p;
  SDL_Rect robitFirstRect = { p.x, p.y, 32, 32 };
  SDL_Rect robitSecondRect = { q.x, q.y, 32, 32 };
  bool isColliding = false;
  if(SDL_HasIntersection(&robitFirstRect, &robitSecondRect)) {
    isColliding = true;
  }
  
  for(auto& r : _robits) { // the & suffix means "reference to"
    if(isColliding == true) {
      isColliding = false;
      r->doCollision();
    } else {
      r->doEvent(mouseX, mouseY);
    }
  }
  block->doEvent(mouseX, mouseY);
  Render();
}

void Scene::Render()
{
  
}
