#include "engine.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if(!init()){
        std::cout << "Initialization failed!" << std::endl;
    }else{
        if(!loadMedia()){
            std::cout << "Filed to load media!" << std::endl;
        }else{
            //Apply the image
            SDL_BlitSurface( gHelloWorld, nullptr, gScreenSurface, nullptr);

            //Update the surface
            SDL_UpdateWindowSurface(gWindow);

            //Waint two seconds
            SDL_Delay(2000);
        }
    }

    close();

    std::cout << "Pass" << std::endl;
    return 0;
}