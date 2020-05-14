#include <SDL2/SDL.h>

#ifndef __ENGINE__
#define __ENGINE__

//Screen dimension constants
const int SCREEN_WIDTH = 509;
const int SCREEN_HEIGHT = 900;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The image we will load and show on the screen
extern SDL_Surface* gHelloWorld;

//Start up SDL and creates window
bool init();

//Load the media
bool loadMedia();

//Free media and shuts down SDL
void close();

#endif