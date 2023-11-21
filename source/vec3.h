#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <string>
// using namespace std;

class Vec3 {
    public:
        double x; double y; double z;

        // Vec3();
        Vec3(double x_in=0, double y_in=0, double z_in=0);
        Vec3(const Vec3& other);

        Vec3 operator + (const Vec3& obj);
        Vec3 operator - (const Vec3& obj);
        Vec3 operator * (const double& factor);
        Vec3 operator / (const double& factor);

        double magSquared();
        double mag();

        Vec3 normalized();
        Vec3 floored();
        Vec3 clampedPositive();
        double dot(const Vec3& with);
        Vec3 cross(const Vec3& with);
        Vec3 a(const Vec3& with);
        Vec3 projectOnto(Vec3& base);
        Vec3 reflect(Vec3& normal);

        void output();
        std::string toString();
};

#endif