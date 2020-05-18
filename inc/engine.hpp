#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace Engine {
//Screen dimension constants
const int SCREEN_WIDTH = 396;
const int SCREEN_HEIGHT = 700;

//Key press surfaces constants
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The surface contained by the window
extern SDL_Surface* gScreenSurface;

//The image we will load and show on the screen
extern SDL_Surface* gBackGround;

//Current displayed image
extern SDL_Surface* gCurrentSurface;

//The images that correspond to a keypress
extern SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Start up SDL and creates window
bool init();

//Load a surface
SDL_Surface* loadSurface(const char* path);

//Load the media
bool loadMedia();

//Free media and shuts down SDL
void close();

//Calculate the run time
double runTime();

}  // namespace Engine