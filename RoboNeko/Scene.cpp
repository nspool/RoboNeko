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
}

void Scene::Add(Sprite *sprite)
{
  _sprites.push_back(sprite);
}



void Scene::doEvent(SDL_Point *p)
{

  // Collision detection
  
  
  // Set the same goal for each of the robits

  for(auto& r : _sprites) { // the & suffix means "reference to"
    r->setGoal(p);
  }
  
  for(auto& r : _sprites) {
    r->render();
  }
}
