#ifndef VEC3_H
#define VEC3_H

class Vec3 {
    public:
        double x; double y; double z;

        Vec3();
        Vec3(double x_in, double y_in, double z_in);

        Vec3 operator + (const Vec3& obj);
        Vec3 operator - (const Vec3& obj);
        Vec3 operator * (const double& factor);
        Vec3 operator / (const double& factor);

        double length_squared();
        double length();

        Vec3 normalized();
        double dot(const Vec3& with);
        Vec3 cross(const Vec3& with);

        void output();
        
};

#endif