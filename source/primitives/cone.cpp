#include "cone.h"
#include "disk.h"
#include "conebody.h"
#include "../compositeshape.h"

Cone::Cone(Vec3 position_in, Vec3 direction_in, double radius_in, double height_in) {
    shapes = {};
    
    ConeBody* body = new ConeBody(position_in, direction_in, radius_in, height_in);
    Disk* lid = new Disk(position_in, direction_in*(-1), radius_in);

    addShape(body);
    addShape(lid);
};

void Cone::setColor(SDL_Color color_in) {
    for (auto shape : shapes) {
        shape->color.r = color_in.r;
        shape->color.g = color_in.g;
        shape->color.b = color_in.b;
        shape->color.a = color_in.a;
    }
};