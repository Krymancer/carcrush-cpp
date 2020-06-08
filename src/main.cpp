#include <iostream>
#include <vector>

#include "engine/engine.hpp"
#include "game/Enemy.hpp"
#include "game/Player.hpp"

bool loadMedia();
void render();
void close();
void update();
void restart();

const int ENEMIESAMMOUNT = 3;
bool gameOver = false;
bool pause = false;

LTexture bg;
Player player;
std::vector<Enemy *> enemies;

int main(int argc, char **argv) {
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
                            case SDLK_r:
                                restart();
                                break;
                            case SDLK_p:
                                pause = !pause;
                                break;
                            default:
                                break;
                        }
                    }
                }

                if (!gameOver && !pause) {
                    // Update everything
                    update();

                    // Clear screen
                    SDL_SetRenderDrawColor(Engine::gRenderer, 0xff, 0xff, 0xff, 0xff);
                    SDL_RenderClear(Engine::gRenderer);

                    // Render everything
                    render();

                    //Update screen
                    SDL_RenderPresent(Engine::gRenderer);
                }
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

    for (int i = 0; i < ENEMIESAMMOUNT; i++) {
        enemies.push_back(new Enemy());
        enemies[i]->init(i);
    }

    return assetsStatus;
}

void render() {
    bg.draw(0, 0);
    player.show();

    for (auto &enemy : enemies) {
        enemy->show();
    }
}

void update() {
    player.update();

    for (auto &enemy : enemies) {
        enemy->update();
        if(player.collide(*enemy)){
            gameOver = true;
            break;
        }
    }
}

void close() {
    bg.free();
}

void restart() {
    for (auto &enemy : enemies) {
        enemy->setStartPosition();
        gameOver = false;
    }
}