#include <engine/LTexture.hpp>

LTexture::LTexture() {
    this->mTexture = nullptr;
    this->mWidth = 0;
    this->mHeight = 0;
}

LTexture::~LTexture() {
    this->free();
}

bool LTexture::loadFromFile(const char* path) {
    //Get rid of the preexisting texutre
    this->free();

    //The final texture
    SDL_Texture* newTexture = nullptr;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image "
                  << path
                  << " SDL_Image_Error: " << IMG_GetError() << std::endl;
    } else {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x0, 0x0, 0x0));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(Engine::gRenderer, loadedSurface);

        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from "
                      << path
                      << " SDL_Error: " << SDL_GetError() << std::endl;
        } else {
            //Get image dimensions
            this->mWidth = loadedSurface->w;
            this->mHeight = loadedSurface->h;
        }

        //Get rid of the old surface
        SDL_FreeSurface(loadedSurface);
    }

    this->mTexture = newTexture;
    return mTexture != nullptr;
}

void LTexture::free() {
    //Free image if exists
    if (this->mTexture != nullptr) {
        SDL_DestroyTexture(this->mTexture);
        this->mTexture = nullptr;
        this->mWidth = 0;
        this->mHeight = 0;
    }
}

void LTexture::draw(int x, int y) {
    //Set rendering space
    SDL_Rect renderQuad = {x, y, this->mWidth, this->mHeight};

    //Render to screen
    SDL_RenderCopy(Engine::gRenderer, this->mTexture, nullptr, &renderQuad);
}

void LTexture::draw(int x, int y, int dx, int dy, int w, int h) {
    //Set clip space
    SDL_Rect clip = {dx, dy, w, h};

    //Set rendering space
    SDL_Rect renderQuad = {x, y, w, h};

    //Render to screen
    SDL_RenderCopy(Engine::gRenderer, this->mTexture, &clip, &renderQuad);
}

int LTexture::getWidth() {
    return this->mWidth;
}

int LTexture::getHeight() {
    return this->mHeight;
}