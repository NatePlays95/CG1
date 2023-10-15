#ifndef ROTATION_H
#define ROTATION_H

#include "mat4.h"
#include <array>

class Rotations{
    public:
        Mat4 rotationX(double x);
        Mat4 rotationY(double x);
        Mat4 rotationZ(double x);
        Mat4 translate(double x, double y, double z);
        Mat4 scale(double x, double y, double z);
        Mat4 screw(double x, double y, double z);
};

#endif;