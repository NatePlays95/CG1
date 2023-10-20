#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

class PointLight : public Light {
public:
    PointLight(Vec3 position_in, Vec3 intensity_in);

    Vec3 calculateDiffuseIntensity(Ray * raycast);
    Vec3 calculateSpecularIntensity(Ray * raycast);
    Vec3 calculateHitIntensity(SDL_Renderer* renderer, Ray * raycast);
};

#endif