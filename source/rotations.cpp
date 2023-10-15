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

Mat4 Rotations::translate(double x, double y, double z) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(1, 0, 0, x));
    m.setColumn(1, Vec4(0, 1, 0, y));
    m.setColumn(2, Vec4(0, 0, 1, z));
    m.setColumn(3, Vec4(0, 0, 0, 1));

    return m;
}

Mat4 Rotations::scale(double x, double y, double z) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(x, 0, 0, 0));
    m.setColumn(1, Vec4(0, y, 0, 0));
    m.setColumn(2, Vec4(0, 0, z, 0));
    m.setColumn(3, Vec4(0, 0, 0, 1));

    return m;
}

Mat4 Rotations::screw(double x, double y, double z) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4( 0, -z,  y, 0));
    m.setColumn(1, Vec4( z,  0, -x, 0));
    m.setColumn(2, Vec4(-y,  x,  0, 0));
    m.setColumn(3, Vec4( 0,  0,  0, 1));
}

