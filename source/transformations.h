#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "mat4.h"

class Transformations{
    public:
        static Mat4 rotateX(double angleRadians);
        static Mat4 rotateY(double angleRadians);
        static Mat4 rotateZ(double angleRadians);
        static Mat4 translate(double x, double y, double z);
        static Mat4 scale(double x, double y, double z);
        static Mat4 screw(double x, double y, double z);

        static Mat4 shearXY(double lambda);
        static Mat4 shearYX(double lambda);
        static Mat4 shearXZ(double lambda);
        static Mat4 shearZX(double lambda);
        static Mat4 shearYZ(double lambda);
        static Mat4 shearZY(double lambda);

        static Mat4 rotateXAroundPoint(double angleRadians, Vec3 center);
        static Mat4 rotateYAroundPoint(double angleRadians, Vec3 center);
        static Mat4 rotateZAroundPoint(double angleRadians, Vec3 center);
        static Mat4 scaleAroundPoint(double sx, double sy, double sz, Vec3 center);
};

#endif