#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray{
    public:
        Vec3 position;
        Vec3 direction; //should be normalized

        Ray();
        Ray(Vec3 position_in);
        Ray(Vec3 position_in, Vec3 direction_in);


        void pointTowards(Vec3 target);
};

#endif