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

void Scene::add(Sprite *sprite)
{
  _sprites.push_back(sprite);
}

void Scene::render(SDL_Point *p)
{
  for(auto& r : _sprites) {
    r->render(p);
  }
}
