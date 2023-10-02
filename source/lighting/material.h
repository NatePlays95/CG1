#ifndef MATERIAL_H
#define MATERIAL_H

#include "../vec3.h"

class Material {
    public:
        Vec3 specular;
        Vec3 roughness;
        double hardness;

        Material(Vec3 specular_in = Vec3(1,1,1), Vec3 roughness_in = Vec3(1,1,1), double hardness_in = 1.0);
};

#endif