#include <engine/LTexture.hpp>
#include <engine/engine.hpp>

#pragma once

class Player {
   public:
    Player();
    ~Player();

    /// Update method
    void update();

    /// Show the car texture
    void show();

    /**
    *  Initilizate the texture
    * 
    *  @returns if the initialization was sucessfully
    */
    bool init();

    /**
    *  Move the player in determinaded direction
    * 
    *  @param direction Correspondent direction to move
    */
    void move(int direction);

    enum directions { LETF,RIGHT};

   private:
    LTexture mTexture;
    int x, y;
    int offset = 78;
};