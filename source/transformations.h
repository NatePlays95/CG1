#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "mat4.h"

class Transformations{
    public:
        static Mat4 rotateX(double angle_radians);
        static Mat4 rotateY(double angle_radians);
        static Mat4 rotateZ(double angle_radians);
        static Mat4 translate(double x, double y, double z);
        static Mat4 scale(double x, double y, double z);
        static Mat4 screw(double x, double y, double z);

        static Mat4 rotateXAroundPoint(double angle_radians, Vec3 center);
        static Mat4 rotateYAroundPoint(double angle_radians, Vec3 center);
        static Mat4 rotateZAroundPoint(double angle_radians, Vec3 center);
        static Mat4 scaleAroundPoint(double sx, double sy, double sz, Vec3 center);
};

#endif