#ifndef CYLINDERBODY_H
#define CYLINDERBODY_H

#include "../shape.h"
#include "../ray.h"

class CylinderBody : public Shape {
    public:
        Vec3 direction;
        double radius;
        double height;
        SDL_Color color;

        CylinderBody();
        CylinderBody(Vec3 position_in, Vec3 direction_in, double radius_in, double height_in);

        bool intersect(Ray& raycast);
};

#endif