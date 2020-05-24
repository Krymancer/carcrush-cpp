#include "engine.hpp"

#include <iostream>

namespace Engine {

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The surface contained by the window
SDL_Surface* gScreenSurface = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

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
            //Create renderer to window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == nullptr) {
                std::cout << "Renderer cloud not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return false;
            } else {
                //Initiaize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

                //Initializing PNG load
                if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) {
                    std::cout << "SDL_Image cloud not initalize! SDL_Image_Error: " << IMG_GetError() << std::endl;
                    return false;
                } else {
                    //Get screen surface
                    gScreenSurface = SDL_GetWindowSurface(gWindow);
                }
            }
        }
    }
    return true;
}

bool loadMedia() {
    return true;
}

void close() {
    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    //Quit SDL subsystems
    IMG_Quit();
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

SDL_Texture* loadTexture(const char* path) {
    //Final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = loadSurface(path);
    if (loadSurface == nullptr) {
        std::cout << "Unable to load image "
                  << path
                  << " SDL_Image_Error: " << IMG_GetError() << std::endl;
        return nullptr;
    } else {
        //Create a texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from "
                      << path
                      << " SDL_Error: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        //Get rid of the old surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

}  // namespace Engine