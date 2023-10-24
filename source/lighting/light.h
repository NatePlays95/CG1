#ifndef LIGHT_H
#define LIGHT_H

#include "../worldobject.h"
#include "../ray.h"

class Light : public WorldObject {
public:
    Vec3 intensity;

    Light(Vec3 position_in, Vec3 intensity_in=Vec3(1,1,1));

    // virtual Vec3 calculateDiffuseIntensity(Ray * raycast) = 0;
    // virtual Vec3 calculateSpecularIntensity(Ray * raycast) = 0;
    virtual Vec3 getLVector(Vec3 incidentPosition) = 0;
    virtual double getIncidenceDistance(Vec3 incidentPosition) = 0;
    virtual Vec3 calculateHitIntensity(SDL_Renderer* renderer, Ray * raycast) = 0;
};

#endif