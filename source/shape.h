#ifndef SHAPE_H
#define SHAPE_H

#include "worldobject.h"
#include "ray.h"
#include "lighting/material.h"

class Shape : public WorldObject {
    public:
        SDL_Color color;
        Material material = Material();

        Shape();

        virtual bool intersect(Ray& raycast) = 0; //abstract
        virtual void printToConsole(); //abstract
};

#endif