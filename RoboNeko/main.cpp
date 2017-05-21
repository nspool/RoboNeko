//
//  main.cpp
//  RoboNeko
//
//  Created by nspool on 8/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <iostream>

#include <OpenGL/gl.h>

#include "Scene.hpp"
#include "Robit.hpp"

SDL_Surface* _background = 0;
SDL_Renderer* _renderer = 0;

constexpr unsigned int WINDOW_WIDTH = 640;
constexpr unsigned int WINDOW_HEIGHT = 480;

bool isMobile = false;
int mouseX = 0;
int mouseY = 0;
int oldMouseX = 0;
int oldMouseY = 0;
int windowX = 0;
int windowY = 0;
int currentTranceDirection = 0;

SDL_Surface *load_image(std::string filename)
{
  SDL_Surface* loadedImage = 0;
  SDL_Surface* optimisedImage = 0;
  
  loadedImage = SDL_LoadBMP(filename.c_str());
  
  SDL_FreeSurface(loadedImage);
  
  return optimisedImage;
}

int
event_filter(void* userdata, SDL_Event* event)
{
  if(isMobile == 1) {
    switch(event->type) {
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEMOTION:
      case SDL_MOUSEBUTTONUP:
        return 0;
    }
  } else {
    switch(event->type) {
      case SDL_FINGERDOWN:
      case SDL_FINGERMOTION:
      case SDL_FINGERUP:
        return 0;
    }
  }
  return 1;
}

int main(int argc, const char * argv[]) {
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0 )
  {
    std::cout << "Failed to initialise SDL!" << std::endl;
    return 1;
  }
  
  if(IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG) < 0)
  {
    std::cout << "Failed to initialise SDL_image!" << std::endl;
    return 1;
  }
  
  // Check platform
  const char* platform = SDL_GetPlatform();
  if(platform[0] == 'i' || platform[0] == 'A') {
    isMobile = 1;
  }
  SDL_SetEventFilter(event_filter, NULL);
  
  //Create window
   SDL_Window* window = SDL_CreateWindow("RoboNeko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN );

  SDL_SetWindowTitle(window, "RoboNeko");
  
  if(window == 0)
  {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }
  
  _renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
  
  if(_renderer == 0)
  {
    printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
    return 1;
  }
  
  // Initialize renderer color
  SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );

  // Initialize
  Scene* scene = new Scene(_renderer);
  
  SDL_Point startingPoint = {(int)arc4random_uniform(WINDOW_WIDTH), (int)arc4random_uniform(WINDOW_HEIGHT)};
  
  Sprite* robit = new Robit(_renderer, startingPoint);
  
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
  
    SDL_GetWindowPosition(window, &windowX, &windowY);
    SDL_GetGlobalMouseState(&mouseX, &mouseY);
    SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0 );
    SDL_RenderClear(_renderer);
    SDL_Point mountPoint = {mouseX - windowX, mouseY - windowY};
    scene->render(&mountPoint);

    SDL_RenderPresent(_renderer);
    
  } while(!quit);
  
  //Destroy window
  SDL_DestroyWindow(window);
  
  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}
