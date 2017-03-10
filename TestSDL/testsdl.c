#include <SDL.h>
#include <stdio.h>

const int WIDTH=800;
const int HEIGH=600;

int main()
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	
	if( SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("failed to init SDL :(\n");
		return;
	} else {
		window = SDL_CreateWindow("Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGH, SDL_WINDOW_SHOWN);
		if(window == NULL){
			printf("no window :(\n");
			return;
		}
		screenSurface = SDL_GetWindowSurface(window);
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0x00));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(2000);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	
	return 0;
}
