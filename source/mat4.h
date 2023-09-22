#ifndef MAT4_H
#define MAT4_H

#include <cmath>
#include <array>
#include "vec4.h"

// Column-Major Order
// 0  4   8  12
// 1  5   9  13
// 2  6  10  14
// 3  7  11  15



class Mat4 {
public:
    std::array<double, 16> mat = 
        {0,0,0,0,
         0,0,0,0,
         0,0,0,0,
         0,0,0,0};

    Mat4();
    Mat4(Mat4& source);

    Mat4 operator + (const Mat4& obj);
    Mat4 operator - (const Mat4& obj);

    Mat4 operator * (double factor);
    Mat4 operator / (double factor);

    Vec4 operator * (const Vec4& vector);
    Mat4 operator * (Mat4& with);

    double at(int line, int column);
    Mat4* set(int line, int column, double value);
    Mat4 setLine(int l, const Vec4& vector);
    Mat4 setColumn(int c, const Vec4& vector);

    static Mat4 scaleMatrix(double sx, double sy, double sz);
};



#endif