#include <SDL2/SDL.h>
#include "material.h"

Material::Material(Vec3 ambient_in, Vec3 roughness_in, Vec3 specular_in, double hardness_in) {
    ambient = ambient_in;
    specular = specular_in;
    roughness = roughness_in;
    hardness = hardness_in;
};