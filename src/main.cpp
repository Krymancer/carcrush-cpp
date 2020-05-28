#include <iostream>

#include "engine/engine.hpp"

void render();
bool load();
void close();

LTexture bg;
LTexture car;

int main(int argc, char** argv) {
    if (!Engine::init()) {
        std::cout << "Initialization failed!" << std::endl;
    } else {
        load();
        if (!Engine::loadMedia()) {
            std::cout << "Failed to load media!" << std::endl;
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

    close();
    Engine::close();

    std::cout << "[PASS]" << std::endl;
    return 0;
}

bool load() {
    bg.loadFromFile("./assets/png/bg.png");
    car.loadFromFile("./assets/png/blue.png");

    return true;
}

void render() {
    bg.draw(0, 0);
    car.draw(96, 540);
    car.draw(10,10,10,10,30,30);
}

void close() {
    bg.free();
    car.free();
}