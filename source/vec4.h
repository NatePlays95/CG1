#ifndef VEC4_H
#define VEC4_H

#include <cmath>
#include "vec3.h"

class Vec4 {
    public:
        double x; double y; double z; double w;

        // Vec3();
        Vec4(double x_in=0, double y_in=0, double z_in=0, double w_in=0);
        Vec4(const Vec4& source);
        Vec4(const Vec3& source, double w_in=1);

        Vec4 operator + (const Vec4& obj);
        Vec4 operator - (const Vec4& obj);
        Vec4 operator * (const double& factor);
        Vec4 operator / (const double& factor);

        double magSquared();
        double mag();

        Vec4 normalized();
        Vec4 floored();
        Vec4 clampedPositive();
        // double dot(const Vec3& with);
        // Vec3 cross(const Vec3& with);
        // Vec3 a(const Vec3& with);
        // Vec3 projectOnto(Vec3& base);
        // Vec3 reflect(Vec3& normal);
        
};

#endif