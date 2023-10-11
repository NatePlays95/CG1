#include "vec4.h"


Vec4::Vec4(double x_in, double y_in, double z_in, double w_in) {
    x = x_in;
    y = y_in;
    z = z_in;
    w = w_in;
};

//copy constructor
Vec4::Vec4(const Vec4& source) {
    x = source.x;
    y = source.y;
    z = source.z;
    w = source.w;
};

//copy constructor from Vec3
Vec4::Vec4(const Vec3& source, double w_in) {
    x = source.x;
    y = source.y;
    z = source.z;
    w = w_in;
};

Vec3 Vec4::to3() {
    return Vec3(x, y, z);
};

Vec4 Vec4::operator + (const Vec4& obj) {
    Vec4 temp = Vec4(*this);
    temp.x += obj.x;
    temp.y += obj.y;
    temp.z += obj.z;
    temp.w += obj.w;
    return temp;
}

Vec4 Vec4::operator - (const Vec4& obj) {
    Vec4 temp = Vec4(*this);
    temp.x -= obj.x;
    temp.y -= obj.y;
    temp.z -= obj.z;
    temp.w -= obj.w;
    return temp;
}

Vec4 Vec4::operator * (const double& factor) {
    Vec4 temp = Vec4(*this);
    temp.x *= factor;
    temp.y *= factor;
    temp.z *= factor;
    temp.w *= factor;
    return temp;
}

Vec4 operator * (const double& factor, Vec4& vector) {
    Vec4 temp = Vec4(vector);
    temp.x *= factor;
    temp.y *= factor;
    temp.z *= factor;
    temp.w *= factor;
    return temp;
}

Vec4 Vec4::operator / (const double& factor) {
    Vec4 temp = Vec4(*this);
    temp.x /= factor;
    temp.y /= factor;
    temp.z /= factor;
    temp.w /= factor;
    return temp;
}

double Vec4::magSquared() { //to save on performance
    return x*x + y*y + z*z + w*w;
}

double Vec4::mag() {
    return sqrt(magSquared());
}

Vec4 Vec4::normalized() {
    Vec4 temp;
    temp = *this / this->mag();
    return temp;
}

Vec4 Vec4::floored() {
    Vec4 temp = Vec4(0,0,0);
    temp.x = floor(this->x);
    temp.y = floor(this->y);
    temp.z = floor(this->z);
    temp.w = floor(this->w);
    return temp;
}

Vec4 Vec4::clampedPositive() {
    Vec4 temp = Vec4(0,0,0);
    temp.x = x < 0 ? 0 : x;
    temp.y = y < 0 ? 0 : y;
    temp.z = z < 0 ? 0 : z;
    temp.w = w < 0 ? 0 : w;
    return temp;
}

// double Vec4::dot(const Vec4& with) {
//     return x*with.x + y*with.y + z*with.z + w*with.w;
// }


// Vec4 Vec4::a(const Vec4& with) {
//     Vec4 temp = Vec4(0,0,0);
//     temp.x *= x*with.x;
//     temp.y *= y*with.y;
//     temp.z *= z*with.z;
//     temp.w *= w*with.w;
//     return temp;
// }

// Vec4 Vec4::projectOnto(Vec4& base) {
//     double scalar = base.dot(*this) / base.dot(base);
//     return base * scalar;
// }

// Vec4 Vec4::reflect(Vec4& normal) {
//     Vec4 copy = Vec4(*this);
//     return copy - 2 * normal.dot(*this) * normal;
// }
