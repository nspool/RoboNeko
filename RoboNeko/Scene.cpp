//
//  Scene.cpp
//  RoboNeko
//
//  Created by nsp on 29/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Scene.hpp"

// TODO: scene graph data structure

Scene::Scene(SDL_Renderer* renderer)
{
  _renderer = renderer;
  block = new Block(renderer);
}

void Scene::Add(Robit *robit)
{
  _robits.push_back(robit);
}



void Scene::doEvent(SDL_Point *p)
{

  // Collision detection
  
  
  // Set the same goal for each of the robits

  for(auto& r : _robits) { // the & suffix means "reference to"
    r->setGoal(p);
  }
  
  for(auto& r : _robits) {
    r->render();
  }
  
  block->render();
}
