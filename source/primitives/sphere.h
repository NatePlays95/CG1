#ifndef SPHERE_H
#define SPHERE_H

#include "../shape.h"
#include "../ray.h"

class Sphere : public Shape {
    public:
        double radius;
        SDL_Color color;

        Sphere();
        Sphere(Vec3 position_in, double radius_in);

        bool intersect(Ray& raycast);
};

#endif