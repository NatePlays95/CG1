#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "mat4.h"

class Transformations{
    public:
        Mat4 rotateX(double angle_radians);
        Mat4 rotateY(double angle_radians);
        Mat4 rotateZ(double angle_radians);
        Mat4 translate(double x, double y, double z);
        Mat4 scale(double x, double y, double z);
        Mat4 screw(double x, double y, double z);

        Mat4 rotateXAroundPoint(double angle_radians, Vec3 center);
        Mat4 rotateYAroundPoint(double angle_radians, Vec3 center);
        Mat4 rotateZAroundPoint(double angle_radians, Vec3 center);
        Mat4 scaleAroundPoint(double sx, double sy, double sz, Vec3 center);
};

#endif