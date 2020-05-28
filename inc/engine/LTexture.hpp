#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <engine/engine.hpp>
#include <iostream>

class LTexture {
   public:
    LTexture();   //Constructor
    ~LTexture();  //Destructor

    /**
    *   Load image from specified path
    * 
    *  @param path Path correspondent to image
    * 
    *  @returns Return true if the image load sucessfully
    */
    bool loadFromFile(const char* path);

    /// Dealocate the texture
    void free();

    /**
    * Render texture at the given point
    * 
    * @param x The x-axis cordinate to place the top-left corner of the texure
    * @param y The y-axis cordinate to place the top-left corner of the texure
    */
    void draw(int x, int y);

    /**
    * Render texture at the given point
    * 
    * @param x  The x-axis cordinate to place the top-left corner of the texure
    * @param y  The y-axis cordinate to place the top-left corner of the texure
    * @param dx The x-axis cordinates to clip the texture
    * @param dy The y-axis cordinates to clip the texture
    * @param w  The width of the clip
    * @param h  The height of the clip
    */
    void draw(int x, int y, int dx, int dy, int w, int h);

    /// Get the width of the texture
    int getWidth();

    /// Get the height of the texture
    int getHeight();

   private:
    /// The actual hardware texture
    SDL_Texture* mTexture;

    /// Image width
    int mWidth;

    /// Image height
    int mHeight;
};