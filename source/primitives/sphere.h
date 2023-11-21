#ifndef SPHERE_H
#define SPHERE_H

#include "../shape.h"
#include "../ray.h"

class Sphere : public Shape {
    public:
        double radius;

        Sphere();
        Sphere(Vec3 position_in, double radius_in);

        void printToConsole();

        bool intersect(Ray& raycast);
};

#endif