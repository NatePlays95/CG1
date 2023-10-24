#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "light.h"

class SpotLight : public Light {
public:
    SpotLight(Vec3 position_in, Vec3 intensity_in, Vec3 direction_in, double openingAngle_in);
    Vec3 direction;
    double openingAngle;

    // Vec3 calculateDiffuseIntensity(Ray * raycast);
    // Vec3 calculateSpecularIntensity(Ray * raycast);
    Vec3 getLVector(Vec3 incidentPosition);
    double getIncidenceDistance(Vec3 incidentPosition);
    Vec3 calculateHitIntensity(SDL_Renderer* renderer, Ray * raycast);
};

#endif