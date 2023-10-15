#include "rotations.h"
#include <cmath> 

Mat4 Rotations::rotationX(double x) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(1, 0, 0, 0));
    m.setColumn(1, Vec4(cos(x), -sin(x), 0, 0));
    m.setColumn(2, Vec4(0, sin(x), cos(x), 0));
    m.setColumn(3, Vec4(0, 0, 0, 1));
    return m;
}

Mat4 Rotations::rotationY(double x) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(cos(x) ,0 ,sin(x), 0));
    m.setColumn(1, Vec4(0 ,1 ,0 ,0));
    m.setColumn(2, Vec4(-sin(x) , 0, cos(x), 0));
    m.setColumn(3, Vec4(0, 0, 0, 1));
    return m;
}

Mat4 Rotations::rotationZ(double x) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(cos(x) , -sin(x), 0, 0));
    m.setColumn(1, Vec4(0, 0, 0, 0));
    m.setColumn(2, Vec4(sin(x) , cos(x), 0, 0));
    m.setColumn(3, Vec4(0, 0, 0, 0));
    return m;
}