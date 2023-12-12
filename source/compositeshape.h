#ifndef COMPOSITESHAPE_H
#define COMPOSITESHAPE_H

#include <list>
#include <string>
#include "ray.h"
#include "shape.h"

class CompositeShape : public Shape {
    public:
        std::list<Shape*> shapes;
        std::string name = "composite_object";
        
        CompositeShape();

        void addShape(Shape* shape);
        void setMaterial(Material material);
        void printToConsole();

        bool intersect(Ray& raycast);
};

#endif