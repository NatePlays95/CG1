#include "compositeshape.h"

bool CompositeShape::intersect(Ray& raycast) {
    bool result = false;
    
    for (auto &shape : shapes) {
        result = shape->intersect(raycast) || result;
    }

    return result;
}