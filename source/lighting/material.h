#ifndef MATERIAL_H
#define MATERIAL_H

#include "../vec3.h"

class Material {
    public:
        Vec3 specular;
        Vec3 roughness;

        Material(Vec3 specular_in = Vec3(1,1,1), Vec3 roughness_in = Vec3(1,1,1));
};

#endif