//
//  Robit.cpp
//  RoboNeko
//
//  Created by nsp on 16/3/17.
//  Copyright 2017 nspool. All rights reserved.
//

#include <cmath>
#include "robit.hpp"
#include "robits.h"

Robit::Robit(SDL_Renderer* renderer, SDL_Point start_pos)
{
  state_ = Pursue;
  
  position_.x = start_pos.x;
  position_.y = start_pos.y;
  position_.w = 21;
  position_.h = 31;
  
  SDL_Surface* gRobits  = SDL_CreateRGBSurfaceFrom((void*)robit_data.pixel_data,
                                                   robit_data.width,
                                                   robit_data.height,
                                                   32,
                                                   robit_data.bytes_per_pixel
                                                   * robit_data.width,
                                                   0x000000ff, 0x0000ff00,
                                                   0x00ff0000, 0xff000000);
  
  if(gRobits == nullptr) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "Failed to load images: %s\n", SDL_GetError());
    return;
  }
  
  for(int i=0; i< (robit_data.width/position_.w); i++) {
    SDL_Rect r = SDL_Rect();
    r.x =i*position_.w;
    r.h = 0;
    r.w = position_.w;
    r.h = robit_data.height;
    frames_.push_back(r);
  }
  
  texture_ = SDL_CreateTextureFromSurface(renderer, gRobits);
  
  transition(Pursue);
}

void Robit::transition(RobitState to_state)
{
  if(to_state == state_) {
    return;
  }
  
  SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Robit: State %d => %d",
              (int)state_, (int)to_state);
  state_ = to_state;
  transition_tm_ = SDL_GetTicks();
}

void Robit::evaluate(SDL_Point* target)
{
  bool target_reached = SDL_PointInRect(target, &position_);
  
  unsigned int diff = (SDL_GetTicks() - transition_tm_);
  
  bool elapsed = (diff > STATE_DELAY_MS);
  
  if(target_reached) {
    if(state_ == Pursue) { transition(Stop); }
    else if(elapsed) {
      switch(state_) {
        case Yawn: transition(Sleep); break;
        case Stop: transition(Wait); break;
        case Wait: transition(Yawn); break;
        default: break;
      }
    }
  } else {
    switch(state_) {
      case Alert: if(elapsed) {transition(Pursue);}; break;
      case Sleep: transition(Alert); break;
      case Stop: transition(Pursue); break;
      case Wait: transition(Pursue); break;
      case Yawn: transition(Alert); break;
      default: break;
    }
  }
  
  if(state_ == Pursue) {
    // Interpolate the line between the current position and the target
    SDL_Rect center = { position_.x + position_.w / 2,
      position_.y + position_.h / 2};
    double rad = atan2((target->y - center.y), (target->x - center.x));
    
    // Set the new coordinates
    double cosr = cos(rad);
    position_.x += cosr > 0.5 ? 1 : cosr < -0.5 ? -1 : 0;
    
    double sinr = sin(rad);
    position_.y += sinr > 0.5 ? 1 : sinr < -0.5 ? -1 : 0;
  }
}

void Robit::render(SDL_Renderer* renderer)
{
  int frame_no = 0;
  
  switch(state_) {
    case Yawn:
      SDL_RenderCopy(renderer, texture_, &frames_[8], &position_);
      break;
    case Sleep:
      frame_no = ((SDL_GetTicks() - transition_tm_) / 1000);
      SDL_RenderCopy(renderer, texture_,
                     &frames_[frame_no % 2 + 5], &position_);
      break;
    case Stop:
      SDL_RenderCopy(renderer, texture_, &frames_[4], &position_);
      break;
    case Alert:
      SDL_RenderCopy(renderer, texture_, &frames_[3], &position_);
      break;
    case Wait:
      SDL_RenderCopy(renderer, texture_, &frames_[7], &position_);
      break;
    case Pursue:
      frame_no = ((SDL_GetTicks() - transition_tm_) * ANIMATION_FPS / 1000);
      SDL_RenderCopy(renderer, texture_, &frames_[frame_no % 3], &position_);
      break;
  }
}
