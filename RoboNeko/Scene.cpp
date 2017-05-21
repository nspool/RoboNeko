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

void Scene::Add(Sprite *sprite)
{
  _sprites.push_back(sprite);
}

void Scene::doEvent(SDL_Point *p)
{
  std::vector<SDL_Rect> obsticles;

  // Update the sprite goals
  for(auto& r : _sprites) {
    r->action(p);
  }
  
  // Render the next frame
  for(auto& r : _sprites) {
    r->render();
  }
}
