#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "worldobject.h"
#include "ray.h"

class Primitive : public WorldObject {
    public:
        Primitive();

        virtual bool intersect(Ray& raycast) = 0; //abstract
};

#endif