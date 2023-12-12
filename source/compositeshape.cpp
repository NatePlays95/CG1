#include "compositeshape.h"
#include <iostream>

CompositeShape::CompositeShape() {
    shapes = {};
};

void CompositeShape::addShape(Shape* shape_in) {
    shapes.push_front(shape_in);
};

void CompositeShape::printToConsole() {
    std::cout << "I'm a CompositeShape object, named " << name << std::endl;
};

bool CompositeShape::intersect(Ray& raycast) {
    bool result = false;
    
    // for (auto &shape : shapes) {
        
    //     bool stepResult = shape->intersect(raycast);
    //     if (!result) result = stepResult;
    // }

    for (auto i : shapes) {
        bool stepResult = i->intersect(raycast);
        if (!result) result = stepResult;
    }

    return result;
};

void CompositeShape::setMaterial(Material material_in) {
    for (auto shape : shapes) {
        shape->material = material_in;
    }
};