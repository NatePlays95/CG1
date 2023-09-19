#include <SDL2/SDL.h>
#include "light.h"

Light::Light(Vec3 position_in, Vec3 intensity_in) {
    position = position_in;
    intensity = intensity_in;
};