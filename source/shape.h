#ifndef SHAPE_H
#define SHAPE_H

#include "worldobject.h"
#include "ray.h"

class Shape : public WorldObject {
    public:
        Shape();

        virtual bool intersect(Ray& raycast) = 0; //abstract
};

#endif