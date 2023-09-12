#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include <list>
#include "ray.h"
#include "shape.h"

class CompositeShape : public Shape {
    public:
        std::list<Shape*> shapes;
        
        CompositeShape();

        void addShape(Shape* shape);

        bool intersect(Ray& raycast);
};

#endif