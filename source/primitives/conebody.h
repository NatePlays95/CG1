#ifndef CONEBODY_H
#define CONEBODY_H

#include "../shape.h"
#include "../ray.h"

class ConeBody : public Shape {
    public:
        Vec3 direction;
        double radius;
        double height;

        ConeBody();
        ConeBody(Vec3 position_in, Vec3 direction_in, double radius_in, double height_in);

        bool intersect(Ray& raycast);
};

#endif