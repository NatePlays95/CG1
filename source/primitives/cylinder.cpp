#include "cylinder.h"
#include "disk.h"
#include "cylinderbody.h"
#include "../compositeshape.h"

Cylinder::Cylinder(Vec3 position_in, Vec3 direction_in, double radius_in, double height_in) {
    shapes = {};
    
    CylinderBody* body = new CylinderBody(position_in, direction_in, radius_in, height_in);
    Disk* lidTop = new Disk(position_in + direction_in*height_in/2, direction_in, radius_in);
    Disk* lidBottom = new Disk(position_in - direction_in*height_in/2, direction_in*(-1), radius_in);

    addShape(body);
    addShape(lidTop);
    addShape(lidBottom);
};

void Cylinder::setColor(SDL_Color color_in) {
    for (auto shape : shapes) {
        shape->color.r = color_in.r;
        shape->color.g = color_in.g;
        shape->color.b = color_in.b;
        shape->color.a = color_in.a;
    }
};