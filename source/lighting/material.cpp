#include <SDL2/SDL.h>
#include "material.h"
#include <iostream>

Material::Material(Vec3 ambient_in, Vec3 roughness_in, Vec3 specular_in, double hardness_in) {
    ambient = ambient_in;
    specular = specular_in;
    roughness = roughness_in;
    hardness = hardness_in;
    texture = nullptr;
};

Vec3 Material::getDiffuseAtUV(SDL_Renderer* renderer, Vec3 uvVec) {
    SDL_Color color = texture->getColorAtUV(uvVec);
    Vec3 texDiffuse = Vec3(color.r, color.g, color.b) / 255.0;
    return texDiffuse;
}

// SDL_Color Material::getColorAtUV(SDL_Renderer* renderer, Vec3 uvVec) {
//     double u = 0; double v = 0; int x = 0; int y = 0;
//     if (!texture) {
//         // Handle the case when the texture is not loaded.
//         return {0, 0, 0, 255}; // Return black or a default color.
//     }

//     // Create a 1x1 off-screen rendering target.
//     // SDL_Surface* surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
//     SDL_Surface* surface = SDL_CreateRGBSurface(0, 1000, 1000, 32, 0, 0, 0, 0);

//     // Calculate the pixel position based on UV coordinates.
//     u = SDL_clamp(uvVec.x, 0.0, 1.0); 
//     v = SDL_clamp(uvVec.y, 0.0, 1.0); 
//     int textureWidth, textureHeight;
//     SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
//     x = static_cast<int>(u * textureWidth);
//     y = static_cast<int>(v * textureHeight);

//     // Render the texture onto the off-screen surface.
//     SDL_Rect srcRect = {x, y, 1, 1};
//     if (SDL_RenderCopy(renderer, texture, &srcRect, NULL) != 0) {
//         // Handle the case when rendering fails.
//         std::cout << SDL_GetError();
//         SDL_FreeSurface(surface);
//         return {0, 0, 0, 255};
//     }

//     // Read the pixel color.
//     Uint32 pixel;
//     if (SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, &pixel, surface->pitch) != 0) {
//         // Handle the case when reading pixels fails.
//         std::cout << SDL_GetError();
//         SDL_FreeSurface(surface);
//         return {0, 0, 0, 255};
//     }

//     // Extract the color information.
//     SDL_Color color;
//     color.a = 255;
//     SDL_GetRGB(pixel, surface->format, &(color.r), &(color.g), &(color.b));

//     // Free the off-screen surface.
//     SDL_FreeSurface(surface);

//     return color;
// };