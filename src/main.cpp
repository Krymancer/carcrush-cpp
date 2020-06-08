#include <iostream>
#include <sstream>
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

LTexture gFPSTextTexture;

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

            //Set text color as black
            SDL_Color textColor = {255, 255, 255, 255};

            //The frames per second timer
            LTimer fpsTimer;

            //In memory text stream
            std::stringstream timeText;

            //Start counting frames per second
            int countedFrames = 0;
            fpsTimer.start();

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

                //Calculate and correct fps
                float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
                if (avgFPS > 2000000) {
                    avgFPS = 0;
                }

                //Set text to be rendered
                timeText.str("");
                timeText << "FPS: " << avgFPS;

                //Render text
                if (!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
                    std::cout << "Unable to render FPS texture!" << std::endl;
                }

                if (!gameOver && !pause) {
                    // Update everything
                    update();
                }

                // Clear screen
                SDL_SetRenderDrawColor(Engine::gRenderer, 0xff, 0xff, 0xff, 0xff);
                SDL_RenderClear(Engine::gRenderer);

                // Render everything
                render();

                //Update screen
                SDL_RenderPresent(Engine::gRenderer);

                ++countedFrames;
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

    assetsStatus &= Engine::loadMedia();

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

    gFPSTextTexture.draw(10, 25);
}

void update() {
    player.update();

    for (auto &enemy : enemies) {
        enemy->update();
        if (player.collide(*enemy)) {
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