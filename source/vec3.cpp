#include <SDL2/SDL.h>
#include "vec3.h"
#include <iostream>
#include <cmath>


Vec3::Vec3(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
};

Vec3::Vec3(double x_in, double y_in, double z_in) {
    this->x = x_in;
    this->y = y_in;
    this->z = z_in;
};



Vec3 Vec3::operator + (const Vec3& obj) {
    Vec3 temp;
    temp.x = this->x + obj.x;
    temp.y = this->y + obj.y;
    temp.z = this->z + obj.z;
    return temp;
}

Vec3 Vec3::operator - (const Vec3& obj) {
    Vec3 temp;
    temp.x = this->x - obj.x;
    temp.y = this->y - obj.y;
    temp.z = this->z - obj.z;
    return temp;
}

Vec3 Vec3::operator * (const double& factor) {
    Vec3 temp;
    temp.x = this->x * factor;
    temp.y = this->y * factor;
    temp.z = this->z * factor;
    return temp;
}

Vec3 Vec3::operator / (const double& factor) {
    Vec3 temp;
    temp.x = this->x / factor;
    temp.y = this->y / factor;
    temp.z = this->z / factor;
    return temp;
}

double Vec3::lengthSquared() { //to save on performance
    return x*x + y*y + z*z;
}

double Vec3::length() {
    return sqrt(lengthSquared());
}

Vec3 Vec3::normalized() {
    Vec3 temp;
    temp = *this / this->length();
    return temp;
}

double Vec3::dot(const Vec3& with) {
    return this->x*with.x + this->y*with.y + this->z*with.z;
}

Vec3 Vec3::cross (const Vec3& with) {
    Vec3 temp;
    temp.x = this->y*with.z - this->z*with.y;
    temp.y = this->x*with.z - this->z*with.x;
    temp.z = this->x*with.y - this->y*with.x;
    return temp;
}


void Vec3::output() {
    std::cout << "[" << this->x << "; " << this->y << "; " << this->z << "]" << std::endl;
}
