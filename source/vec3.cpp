#include <SDL2/SDL.h>
#include "vec3.h"
#include <iostream>


Vec3::Vec3(double x_in, double y_in, double z_in) {
    x = x_in;
    y = y_in;
    z = z_in;
};

//copy constructor
Vec3::Vec3(Vec3& source) {
    x = source.x;
    y = source.y;
    z = source.z;
};

Vec3 Vec3::operator + (const Vec3& obj) {
    Vec3 temp = Vec3(*this);
    temp.x += obj.x;
    temp.y += obj.y;
    temp.z += obj.z;
    return temp;
}

Vec3 Vec3::operator - (const Vec3& obj) {
    Vec3 temp = Vec3(*this);
    temp.x -= obj.x;
    temp.y -= obj.y;
    temp.z -= obj.z;
    return temp;
}

Vec3 Vec3::operator * (const double& factor) {
    Vec3 temp = Vec3(*this);
    temp.x *= factor;
    temp.y *= factor;
    temp.z *= factor;
    return temp;
}

Vec3 operator * (const double& factor, Vec3& vector) {
    Vec3 temp = Vec3(vector);
    temp.x *= factor;
    temp.y *= factor;
    temp.z *= factor;
    return temp;
}

Vec3 Vec3::operator / (const double& factor) {
    Vec3 temp = Vec3(*this);
    temp.x /= factor;
    temp.y /= factor;
    temp.z /= factor;
    return temp;
}

double Vec3::magSquared() { //to save on performance
    return x*x + y*y + z*z;
}

double Vec3::mag() {
    return sqrt(magSquared());
}

Vec3 Vec3::normalized() {
    Vec3 temp;
    temp = *this / this->mag();
    return temp;
}

Vec3 Vec3::floored() {
    Vec3 temp = Vec3(0,0,0);
    temp.x = floor(this->x);
    temp.y = floor(this->y);
    temp.z = floor(this->z);
    return temp;
}

Vec3 Vec3::clampedPositive() {
    Vec3 temp = Vec3(0,0,0);
    temp.x = x < 0 ? 0 : x;
    temp.y = y < 0 ? 0 : y;
    temp.z = z < 0 ? 0 : z;
    return temp;
}

double Vec3::dot(const Vec3& with) {
    return this->x*with.x + this->y*with.y + this->z*with.z;
}

Vec3 Vec3::cross(const Vec3& with) {
    Vec3 temp;
    temp.x = this->y*with.z - this->z*with.y;
    temp.y = this->x*with.z - this->z*with.x;
    temp.z = this->x*with.y - this->y*with.x;
    return temp;
}

Vec3 Vec3::a(const Vec3& with) {
    Vec3 temp = Vec3(0,0,0);
    temp.x *= x*with.x;
    temp.y *= y*with.y;
    temp.z *= z*with.z;
    return temp;
}

Vec3 Vec3::projectOnto(Vec3& base) {
    double scalar = base.dot(*this) / base.dot(base);
    return base * scalar;
}

Vec3 Vec3::reflect(Vec3& normal) {
    Vec3 copy = Vec3(*this);
    return copy - 2 * normal.dot(*this) * normal;
}

void Vec3::output() {
    std::cout << "[" << this->x << "; " << this->y << "; " << this->z << "]" << std::endl;
}
