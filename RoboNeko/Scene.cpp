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
  
  // Quick & Dirty collision detection
  
  for(auto& r : _sprites) {
    for(auto& s : _sprites) {
      if(r == s) { continue; }
      SDL_Rect result = SDL_Rect();
      SDL_Rect r_rect = r->getBounds();
      SDL_Rect s_rect = s->getBounds();
      if(SDL_IntersectRect(&r_rect, &s_rect, &result)== SDL_TRUE) {
        r->doCollision();
      }
    }
  }
  
  // Set the same goal for each of the robits
  
  for(auto& r : _sprites) { // the & suffix means "reference to"
    r->action(p);
  }
  
  for(auto& r : _sprites) {
    r->render();
  }
}
