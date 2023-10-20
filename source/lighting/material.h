#ifndef MATERIAL_H
#define MATERIAL_H

#include "../vec3.h"

class Material {
    public:
        Vec3 ambient;
        Vec3 specular;
        Vec3 roughness;
        double hardness;

        SDL_Texture* texture = nullptr;
        bool hasAlphaClip = false;

        Material(Vec3 ambient_in = Vec3(1,1,1), Vec3 roughness_in = Vec3(1,1,1), Vec3 specular_in = Vec3(1,1,1), double hardness_in = 1.0);

        SDL_Color getColorAtUV(SDL_Renderer* renderer, Vec3 uvVec);
        Vec3 getDiffuseAtUV(SDL_Renderer* renderer, Vec3 uvVec);
};

#endif