#ifndef TEXTURE_H
#define TEXTURE_H

#include "../vec3.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture {
    private:
        SDL_Surface* surface = nullptr;

    public:
        void loadImageBMP (std::string path);
        // Pixel getPixel (int x, int y);
        SDL_Color getColorAtUV(Vec3 uvVec);

        int getImageWidth ();
        int getImageHeight ();

        Texture (std::string path);
        Texture ();
        ~Texture ();

};

#endif