#include "compositeshape.h"

CompositeShape::CompositeShape() {
    shapes = {};
};

void CompositeShape::addShape(Shape* shape_in) {
    shapes.push_front(shape_in);
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