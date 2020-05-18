#include <iostream>

#include "engine.hpp"

int main(int argc, char** argv) {
    if (!Engine::init()) {
        std::cout << "Initialization failed!" << std::endl;
    } else {
        if (!Engine::loadMedia()) {
            std::cout << "Filed to load media!" << std::endl;
        } else {
            //Quit flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            //Set default current surface
            Engine::gCurrentSurface = Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_LEFT];

            while (!quit) {
                //Handle events on qeue
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {  //User request quit
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {  //User press a key
                        switch (e.key.keysym.sym) {
                            case SDLK_UP:
                                Engine::gCurrentSurface = Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_UP];
                                break;
                            case SDLK_DOWN:
                                Engine::gCurrentSurface = Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_DOWN];
                                break;
                            case SDLK_LEFT:
                                Engine::gCurrentSurface = Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_LEFT];
                                break;
                            case SDLK_RIGHT:
                                Engine::gCurrentSurface = Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_RIGHT];
                                break;
                            default:
                                Engine::gCurrentSurface = Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_DEFAULT];
                                break;
                        }
                    }
                }

                //Apply the image
                SDL_BlitSurface(Engine::gBackGround, nullptr, Engine::gScreenSurface, nullptr);

                SDL_Rect stretchRect;
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = Engine::SCREEN_WIDTH;
                stretchRect.h = Engine::SCREEN_HEIGHT;
                SDL_BlitScaled(Engine::gKeyPressSurfaces[Engine::KEY_PRESS_SURFACE_DEFAULT], NULL, Engine::gScreenSurface, &stretchRect);

                //Apply the current image
                SDL_BlitSurface(Engine::gCurrentSurface, nullptr, Engine::gScreenSurface, nullptr);

                //Update the surface
                SDL_UpdateWindowSurface(Engine::gWindow);
            }
        }
    }

    Engine::close();

    std::cout << "[PASS]" << std::endl;
    return 0;
}