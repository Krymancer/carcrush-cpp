#include "engine.hpp"

#include <iostream>

namespace Engine {

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The image we will load and show on the screen
SDL_Surface* gBackGround = nullptr;

//Current displayed image
SDL_Surface* gCurrentSurface = nullptr;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

bool init() {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (gWindow == nullptr) {
            std::cout << "Window cloud not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        } else {
            if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
                std::cout << "SDL_Image cloud not initalize! SDL_Image_Error: " << IMG_GetError() << std::endl;
                return false;
            } else {
                //Get screen surface
                gScreenSurface = SDL_GetWindowSurface(gWindow);
            }
        }
    }
    return true;
}

bool loadMedia() {
    gBackGround = loadSurface("./assets/bmp/street-red.bmp");

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./assets/png/blue.png");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("./assets/bmp/gray.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("./assets/bmp/pink.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("./assets/bmp/purple.bmp");
    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./assets/bmp/green.bmp");

    for (auto media : gKeyPressSurfaces) {
        if (media == nullptr) return false;
    }

    return true;
}

void close() {
    //Dealocate the surface
    SDL_FreeSurface(gBackGround);
    gBackGround = nullptr;

    for (auto media : gKeyPressSurfaces) {
        SDL_FreeSurface(media);
    }

    //Destroy window
    SDL_DestroyWindow(gWindow);

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface(const char* path) {
    //Optimized surface
    SDL_Surface* optimizedSurface = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image "
                  << path
                  << " SDL_Image_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    } else {
        //Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);

        if (optimizedSurface == nullptr) {
            std::cout << "Unable to optimize image "
                      << path
                      << " SDL_Error: " << SDL_GetError() << std::endl;
            return loadedSurface;
        }

        //Get rid of the old surface
        SDL_FreeSurface(loadedSurface);
    }

    return optimizedSurface;
}

}  // namespace Engine