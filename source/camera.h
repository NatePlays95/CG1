#ifndef CAMERA_H
#define CAMERA_H

#include "mat4.h"
#include "ray.h"

class Camera{
    public:
        double frameWidth; double frameHeight; //mudar para Frame
        double frameDistance;

        Vec3 position; //eye
        Vec3 target;

        Vec3 i = Vec3(1,0,0);
        Vec3 j = Vec3(0,1,0);
        Vec3 k = Vec3(0,0,1);

        Camera();

        Mat4 lookAt(Vec3 eye, Vec3 at, Vec3 up_direction);
        Mat4 lookAt(Vec3 at);
        Mat4 cameraToWorldMatrix();

};

#endif