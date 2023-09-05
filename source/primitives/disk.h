#ifndef DISK_H
#define DISK_H

#include "../shape.h"
#include "../ray.h"

class Disk : public Shape {
    public:
        Vec3 normalDirection;
        double radius;
        SDL_Color color;

        Disk();
        Disk(Vec3 position_in, Vec3 normal_in, double radius);

        bool intersect(Ray& raycast);
};

#endif