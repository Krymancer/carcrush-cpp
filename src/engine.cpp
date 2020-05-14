#include "engine.hpp"
#include <iostream>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

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
            //Get screen surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return true;
}

bool loadMedia() {
    //Load splash image
    gHelloWorld = SDL_LoadBMP("./assets/street.bmp");

    if (gHelloWorld == nullptr) {
        std::cout << "Unable to load image "
                  << "./assets/street.bmp"
                  << "SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void close(){
    //Dealocate the surface
    SDL_FreeSurface( gHelloWorld);
    gHelloWorld = nullptr;
    
    //Destroy window
    SDL_DestroyWindow(gWindow);

    //Quit SDL subsystems
    SDL_Quit();
}
