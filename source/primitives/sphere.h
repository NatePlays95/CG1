#ifndef SPHERE_H
#define SPHERE_H

#include "../primitive.h"
#include "../ray.h"

class Sphere : public Primitive {
    public:
        double radius;
        SDL_Color color;

        Sphere();
        Sphere(Vec3 position_in, double radius_in);

        bool intersect(Ray& raycast);
};

#endif