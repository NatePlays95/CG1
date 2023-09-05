#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include <list>
#include "ray.h"
#include "shape.h"

class CompositeShape : public Shape {
    public:
        std::list<Shape*> shapes;
        
        CompositeShape();

        bool intersect(Ray& raycast);
};

#endif