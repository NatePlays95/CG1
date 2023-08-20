#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class Camera{
    public:
        double frameWidth; double frameHeight; //mudar para Frame
        double frameDistance;

        Ray eye;

        Camera();

};

#endif