#include <iostream>

#include "engine.hpp"

void render();

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

            while (!quit) {
                //Handle events on qeue
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {  //User request quit
                        quit = true;
                    } else if (e.type == SDL_KEYDOWN) {  //User press a key
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(Engine::gRenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(Engine::gRenderer);

                render();

                //Update screen
                SDL_RenderPresent(Engine::gRenderer);
            }
        }
    }

    Engine::close();

    std::cout << "[PASS]" << std::endl;
    return 0;
}

void render() {
    //Render red filled square
    SDL_Rect fillRect = {Engine::SCREEN_WIDTH / 4,
                         Engine::SCREEN_HEIGHT / 4,
                         Engine::SCREEN_WIDTH / 2,
                         Engine::SCREEN_HEIGHT / 2};

    SDL_SetRenderDrawColor(Engine::gRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(Engine::gRenderer, &fillRect);

    //Render green outline quad
    SDL_Rect outLineRect = {Engine::SCREEN_WIDTH / 6,
                            Engine::SCREEN_HEIGHT / 6,
                            Engine::SCREEN_WIDTH * 2 / 3,
                            Engine::SCREEN_HEIGHT * 2 / 3};

    SDL_SetRenderDrawColor(Engine::gRenderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderDrawRect(Engine::gRenderer, &outLineRect);

    //Draw blue horizontal line
    SDL_SetRenderDrawColor(Engine::gRenderer, 0x00, 0x00, 0xff, 0xff);
    SDL_RenderDrawLine(Engine::gRenderer, 0, Engine::SCREEN_HEIGHT / 2, Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT / 2);

    //Draw vertical line of yellow dots
    SDL_SetRenderDrawColor(Engine::gRenderer, 0xff, 0xff, 0x00, 0xff);

    for (int i = 0; i < Engine::SCREEN_WIDTH; i += 4) {
        SDL_RenderDrawPoint(Engine::gRenderer, Engine::SCREEN_WIDTH / 2, i);
    }
}