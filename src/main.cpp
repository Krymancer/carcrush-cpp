#include <iostream>

#include "engine.hpp"

int main(int argc, char** argv) {
    if (!init()) {
        std::cout << "Initialization failed!" << std::endl;
    } else {
        if (!loadMedia()) {
            std::cout << "Filed to load media!" << std::endl;
        } else {
            //Quit flag
            bool quit = false;
            //Event handler
            SDL_Event e;

            while (!quit) {
                //Apply the image
                SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);

                //Handle events on qeue
                while (SDL_PollEvent(&e) != 0) {
                    //User request quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }
        }
    }

    close();

    std::cout << "Pass" << std::endl;
    return 0;
}