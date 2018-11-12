//
//  main.cpp
//  RoboNeko
//
//  Created by nspool on 8/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include "Scene.hpp"
#include "Robit.hpp"

#include "robits.h"

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

#ifdef __MINGW32__
#ifdef main
# undef main
#endif /* main */
#endif /* main */

int main(int argc, char * argv[]) {

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0 )
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialise SDL!\n");
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow("RoboNeko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if(window == nullptr)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow: SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(renderer == nullptr)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer: SDL Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_RendererInfo info = {0};
  int ret = SDL_GetRendererInfo(renderer, &info);
  SDL_LogInfo(SDL_LOG_CATEGORY_RENDER, "Using SDL Renderer %s\n", &info.name);

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

    if(SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT) {
          quit = true;
      }
    }

    SDL_Point windowPos = {0};
    SDL_Point mousePos = {0};

    SDL_GetWindowPosition(window, &windowPos.x, &windowPos.y);
    SDL_GetGlobalMouseState(&mousePos.x, &mousePos.y);
    SDL_RenderClear(renderer);

    SDL_Point mousePoint = {mousePos.x - windowPos.x, mousePos.y - windowPos.y};
    scene->render(&mousePoint);

    SDL_RenderPresent(renderer);

  } while(!quit);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
