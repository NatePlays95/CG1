#ifndef RAY_H
#define RAY_H

#include <SDL2/SDL.h>
#include <cmath>
#include "vec3.h"

class Ray{
    public:
        Vec3 position;
        Vec3 direction; //should be normalized
        double t = std::numeric_limits<double>::infinity();
        Vec3 contact_position;
        Vec3 contact_normal;
        SDL_Color contact_color;

        Ray();
        Ray(Vec3 position_in);
        Ray(Vec3 position_in, Vec3 direction_in);

        void pointTowards(Vec3 target);
        bool update_t(double new_t);
};

#endif