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
  
  // Quick & Dirty collision detection
  for(auto& r : _sprites) {
    
    if(r->isObsticle()) {
      obsticles.push_back(r->getBounds());
    }
    
    for(auto& s : _sprites) {
      if(r == s) { continue; }
      SDL_Rect result = SDL_Rect();
      SDL_Rect r_rect = r->getBounds();
      SDL_Rect s_rect = s->getBounds();
      if(SDL_IntersectRect(&r_rect, &s_rect, &result)== SDL_TRUE) {
        r->doCollision(&s_rect);
      }
    }
  }
  
  // Update the sprite goals
  for(auto& r : _sprites) {
    r->action(p, &obsticles);
  }
  
  // Render the next frame
  for(auto& r : _sprites) {
    r->render();
  }
}
