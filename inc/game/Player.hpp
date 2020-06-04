#include <engine/LTexture.hpp>
#include <engine/engine.hpp>
#include <game/Enemy.hpp>

#pragma once

class Player {
   public:
    Player();
    ~Player();

    /**
    *  Initilizate the texture
    * 
    *  @returns if the initialization was sucessfully
    */
    bool init();

    /// Update method
    void update();

    /// Show the car texture
    void show();

    /**
    *  Move the player in determinaded direction
    * 
    *  @param direction Correspondent direction to move
    */
    void move(int direction);

    /**
    *  Check if the player collides with a enemy
    * 
    *  @param enemy the enemy to check
    * 
    *  @returns true with collides
    */
    bool collide(Enemy &enemy);

    /// Directions to use with the move function
    enum directions { LETF,
                      RIGHT };

   private:
    LTexture mTexture;
    int x, y;
    int offset = 78;
};