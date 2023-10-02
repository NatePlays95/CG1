#include <SDL2/SDL.h>
#include "material.h"

Material::Material(Vec3 specular_in, Vec3 roughness_in, double hardness_in) {
    specular = specular_in;
    roughness = roughness_in;
    hardness = hardness_in;
};