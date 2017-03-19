//
//  main.cpp
//  RoboNeko
//
//  Created by nspool on 8/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include <iostream>

#include "Robit.hpp"

SDL_Surface* _background = 0;
SDL_Renderer* _renderer = 0;

int mouseX = 0;
int mouseY = 0;
int oldMouseX = 0;
int oldMouseY = 0;
int currentTranceDirection = 0;

SDL_Surface *load_image(std::string filename)
{
  SDL_Surface* loadedImage = 0;
  SDL_Surface* optimisedImage = 0;
  
  loadedImage = SDL_LoadBMP(filename.c_str());
  
  SDL_FreeSurface(loadedImage);
  
  return optimisedImage;
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
  
  //Create window
  SDL_Window* window = SDL_CreateWindow("RoboNeko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
  
  //Initialize renderer color
  SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    
  bool quit = false;
  
  // event handler
  SDL_Event e;
  
  Robit* r1 = new Robit(_renderer);
  Robit* r2 = new Robit(_renderer);
  
  // Starting position
  r2->p = {0, 100};
  
  // Main event loop
  
  do {
    while(SDL_PollEvent(&e) != 0)
    {
      switch (e.type) {
        case SDL_QUIT:
          quit = true;
        case SDL_MOUSEMOTION:
          SDL_GetMouseState( &mouseX, &mouseY );
        default:
          break;
      }
    }
    
    // Clear window
    SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( _renderer );
    
    r1->doEvent(mouseX, mouseY);
    //    r2->doEvent();
    
    SDL_RenderPresent( _renderer );
    
  } while(!quit);
  
  //Destroy window
  SDL_DestroyWindow(window);
  
  //Quit SDL subsystems
  SDL_Quit();
  
  return 0;
}
