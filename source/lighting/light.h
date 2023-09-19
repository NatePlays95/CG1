#ifndef LIGHT_H
#define LIGHT_H

#include "../worldobject.h"

class Light : public WorldObject {
public:
    Vec3 intensity;

    Light(Vec3 position_in, Vec3 intensity_in=Vec3(1,1,1));
};

#endif