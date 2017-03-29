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
  for(auto& r : _robits) { // the & suffix means "reference to"
    r->doEvent(mouseX, mouseY);
  }
  Render();
}

void Scene::Render()
{
  
}
