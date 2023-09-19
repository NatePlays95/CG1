#ifndef RAY_H
#define RAY_H

#include <SDL2/SDL.h>
#include <cmath>
#include <limits>
#include "vec3.h"
#include "lighting/material.h"

class Ray{
    public:
        Vec3 position;
        Vec3 direction; //should be normalized
        double t = std::numeric_limits<double>::infinity();
        Vec3 contact_position;
        Vec3 contact_normal;
        SDL_Color contact_color;
        Material contact_material;

        //Ray();
        Ray(Vec3 position_in=Vec3(0,0,0), Vec3 direction_in=Vec3(0,0,-1));
        //Ray(Vec3 position_in, Vec3 direction_in);

        void pointTowards(Vec3 target);
        Vec3 contactPosition();
        bool updateT(double new_t, Vec3 new_normal, SDL_Color new_color);
        bool updateT(double new_t, Vec3 new_normal, Material new_material);
};

#endif