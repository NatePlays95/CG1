#ifndef CYLINDER_H
#define CYLINDER_H

#include "../compositeshape.h"

class Cylinder : public CompositeShape {
    public:
        Cylinder(Vec3 position_in, Vec3 direction_in, double radius_in=0, double height_in=0);
        
        void setColor(SDL_Color color_in);
        void setMaterial(Material material_in);
};

#endif