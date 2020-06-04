#include <engine/LTexture.hpp>
#include <engine/engine.hpp>
#include <random>

#pragma once

class Enemy {
   public:
    Enemy();
    ~Enemy();

    /**
    *  Initilizate the texture
    * 
    *  @returns if the initialization was sucessfully
    */
    bool init(int id);

    /// Update method
    void update();

    /// Show the car texture
    void show();

    /// Set the start position of the enemy
    void setStartPosition();

    /// Get the x position of the enemy
    int getX();

    /// Get the y position of the enemy
    int getY();

    /// Get the width position of the enemy
    int getWidth();

    /// Get the height position of the enemy
    int getHeight();

   private:
    LTexture mTexture;
    int x, y;

    int speed = 10;
    int startPositions[4] = {18, 96, 174, 252};
    bool alive = true;
};