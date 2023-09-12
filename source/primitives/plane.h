#ifndef PLANE_H
#define PLANE_H

#include "../shape.h"
#include "../ray.h"

class Plane : public Shape {
    public:
        Vec3 normalDirection;

        Plane();
        Plane(Vec3 position_in, Vec3 normal_in);

        bool intersect(Ray& raycast);
};

#endif