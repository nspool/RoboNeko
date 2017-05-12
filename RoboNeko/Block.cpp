//
//  Block.cpp
//  RoboNeko
//
//  Created by nsp on 1/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Block.hpp"

Block::Block(SDL_Renderer* renderer, SDL_Point p)
{
  _p = p;
  _renderer = renderer;
  
  // Load the robit
  SDL_Surface* gRobits = IMG_Load( "block.png" );
  
  if(gRobits == 0)
  {
    printf( "Failed to load images! SDL_Error: %s\n", SDL_GetError() );
  }
  
  // Setup Robit animation
  spriteClips[0].x = 0;
  spriteClips[0].y = 0;
  spriteClips[0].w = 32;
  spriteClips[0].h = 32;
  
  mTexture = SDL_CreateTextureFromSurface( renderer, gRobits );
}

void Block::render()
{
  SDL_Rect blockLoc = getBounds();
  SDL_RenderCopy( _renderer, mTexture, &spriteClips[0], &blockLoc );
}

void Block::stop(){
  
}

bool Block::isObsticle() {
  return true;
}

SDL_Rect Block::getBounds()
{
  return { _p.x, _p.y, 32, 32 };
}

void Block::doCollision(SDL_Rect* rect)
{
  printf("Block collision\n");
}
