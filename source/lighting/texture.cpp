#include "texture.h"
#include <iostream>

int Texture::getImageWidth () {
    return this->surface->w;
}

int Texture::getImageHeight () {
    return this->surface->h;
}

Texture::Texture () {}

Texture::Texture (std::string path) {
    this->loadImageBMP (path);
}

Texture::~Texture () {
    SDL_UnlockSurface (this->surface);
    SDL_FreeSurface (this->surface);
}

void Texture::loadImageBMP (const std::string path) {

    std::string fullPath = "assets/textures/" + path + ".bmp";
    SDL_Surface* surface = IMG_Load(fullPath.c_str());

    if (surface == nullptr) {
        std::cout << "error on load the image" << std::endl;
        return;
    }

    int lockSurfaceResult = SDL_LockSurface (surface);

    if (lockSurfaceResult != 0) {
        std::cout << "error on lock the texture bytes" << std::endl;
        SDL_FreeSurface (surface);
        return;
    }

    if (this->surface != nullptr) SDL_FreeSurface (this->surface);

    this->surface = surface;
};

SDL_Color Texture::getColorAtUV (Vec3 uvVec) {
    uvVec.y = 1.0 - uvVec.y;
    // uvVec.x = 1.0 - uvVec.x;

    //texture should tile
    uvVec.x -= floor(uvVec.x);
    uvVec.y -= floor(uvVec.y);

    int x = static_cast<int>(uvVec.x * surface->w );
    int y = static_cast<int>(uvVec.y * surface->h );
    
    int bytesPerPixel = this->surface->format->BytesPerPixel;
    Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bytesPerPixel;

    Uint8 r = *(pixel + surface->format->Rshift / 8);
    Uint8 g = *(pixel + surface->format->Gshift / 8);
    Uint8 b = *(pixel + surface->format->Bshift / 8);
    Uint8 a = *(pixel + surface->format->Ashift / 8);

    SDL_Color color = {r, g, b, a};
    return color;
};

// SDL_Color Texture::getColorAtUV (Vec3 uvVec) {
//     int x = static_cast<int>(uvVec.x * getImageWidth());
//     int y = static_cast<int>(uvVec.y * getImageHeight());
//     int selectedPixel;

//     int bytesPerPixel = this->surface->format->BytesPerPixel;
//     // pixel address
//     Uint8* pixel = (Uint8*) this->surface->pixels + y * this->surface->pitch + x * bytesPerPixel;

//     switch (bytesPerPixel) {
//         case 1:
//             selectedPixel = *pixel;
//             break;
//         case 2:
//             selectedPixel = *((Uint16*) pixel);
//             break;
//         case 3:
//             if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
//                 selectedPixel = pixel[0] << 16 | pixel[1] << 8 | pixel[2];
//             } else {
//                 selectedPixel = pixel[0] | pixel[1] << 8 | pixel[2] << 16;
//             }
//             break;
//         case 4:
//             selectedPixel = *((Uint32*)pixel);
//             break;
//         default:
//             selectedPixel = 0;
//     }

//     SDL_Color color;
//     SDL_GetRGBA(selectedPixel, this->surface->format, &color.r, &color.g, &color.b, &color.a);

//     return color;
// }