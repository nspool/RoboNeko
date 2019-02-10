//
//  main.cpp
//  RoboNeko
//
//  Created by nspool on 8/3/17.
//  Copyright 2017 nspool. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include "scene.hpp"
#include "robit.hpp"

#include "robits.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

#ifdef __MINGW32__
#ifdef main
# undef main
#endif
#endif

int main(int argc, char * argv[]) {
  
  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
  
  if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0 )
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialise SDL!\n");
    return EXIT_FAILURE;
  }
  
  SDL_Window* window = SDL_CreateWindow("RoboNeko", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                                        WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  
  if(window == nullptr)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "SDL_CreateWindow: SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                              SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
  
  if(renderer == nullptr)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR,
                    "SDL_CreateRenderer: SDL Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  
  SDL_RendererInfo info = {0};
  SDL_GetRendererInfo(renderer, &info);
  SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Using SDL Renderer %s\n", info.name);
  
  SDL_SetWindowTitle(window, "RoboNeko");
  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0 );
  
  // Don't do alpha blending
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
  
  // Initialize the scene
  Scene* scene = new Scene(renderer);
  Sprite* robit = new Robit(renderer, {WINDOW_WIDTH/2, WINDOW_HEIGHT/2});
  scene->add(robit);
  
  // Main event loop
  
  SDL_Event e;
  bool quit = false;
  
  do {
    
    Uint32 start_tk = SDL_GetTicks();
    
    if(SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    
    SDL_Point win_pos = {0};
    SDL_Point ptr_pos = {0};
    
    SDL_GetWindowPosition(window, &win_pos.x, &win_pos.y);
    SDL_GetGlobalMouseState(&ptr_pos.x, &ptr_pos.y);
    SDL_RenderClear(renderer);
    
    SDL_Point ptr_pt = {ptr_pos.x - win_pos.x, ptr_pos.y - win_pos.y};
    scene->render(&ptr_pt);
    
    SDL_RenderPresent(renderer);
    
    Uint32 endTick = SDL_GetTicks() - start_tk;
    if(endTick < SCREEN_TICKS_PER_FRAME)
    {
      SDL_Delay(SCREEN_TICKS_PER_FRAME - endTick);
    }
    
  } while(!quit);
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
