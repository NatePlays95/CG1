#include <SDL2/SDL.h>
#include "pointlight.h"

PointLight::PointLight(Vec3 position_in, Vec3 intensity_in) : Light(position_in, intensity_in){};