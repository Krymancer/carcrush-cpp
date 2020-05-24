#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Engine {
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The window renderer
extern SDL_Renderer* gRenderer;

//Start up SDL and creates window
bool init();

//Load a surface
SDL_Surface* loadSurface(const char* path);

//Loads individual image as texture
SDL_Texture* loadTexture(const char* path);

//Load the media
bool loadMedia();

//Free media and shuts down SDL
void close();

//Calculate the run time
double runTime();

}  // namespace Engine