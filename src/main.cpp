#include <iostream>

#include "engine/engine.hpp"
#include "game/Player.hpp"

bool loadMedia();
void render();
void close();

LTexture bg;
Player player;

int main(int argc, char** argv) {
    if (!Engine::init()) {
        std::cout << "Initialization failed!" << std::endl;
    } else {
        // load();
        if (!loadMedia()) {
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
                        switch (e.key.keysym.sym) {
                            case SDLK_LEFT:
                                player.move(player.LETF);
                                break;
                            case SDLK_RIGHT:
                                player.move(player.RIGHT);
                                break;
                            default:
                                break;
                        }
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

bool loadMedia() {
    bool assetsStatus = true;

    assetsStatus &= bg.loadFromFile("./assets/png/bg.png");
    assetsStatus &= player.init();

    return assetsStatus;
}

void render() {
    bg.draw(0, 0);
    player.show();
}

void close() {
    bg.free();
}