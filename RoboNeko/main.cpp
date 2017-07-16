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

constexpr unsigned int WINDOW_WIDTH = 640;
constexpr unsigned int WINDOW_HEIGHT = 480;

int main(int argc, const char * argv[]) {
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0 )
  {
    printf("Failed to initialise SDL!\n");
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow("RoboNeko",
                                        SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,
                                        WINDOW_WIDTH, WINDOW_HEIGHT,
                                        SDL_WINDOW_SHOWN);
  if(window == 0)
  {
    printf("SDL_CreateWindow: SDL_Error: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(renderer == 0)
  {
    printf("SDL_CreateRenderer: SDL Error: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_SetWindowTitle(window, "RoboNeko");
  SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  // Initialize
  
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

    int windowX, windowY, mouseX, mouseY;
    SDL_GetWindowPosition(window, &windowX, &windowY);
    SDL_GetGlobalMouseState(&mouseX, &mouseY);
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0 );
    SDL_RenderClear(renderer);
    
    SDL_Point mousePoint = {mouseX - windowX, mouseY - windowY};
    scene->render(&mousePoint);

    SDL_RenderPresent(renderer);
    
  } while(!quit);
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}
