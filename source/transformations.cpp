#include "transformations.h"
#include <cmath> 

Mat4 Transformations::rotateX(double angle) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(1, 0, 0, 0));
    m.setColumn(1, Vec4(cos(angle), -sin(angle), 0, 0));
    m.setColumn(2, Vec4(0, sin(angle), cos(angle), 0));
    m.setColumn(3, Vec4(0, 0, 0, 1));
    return m;
};

Mat4 Transformations::rotateY(double angle) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(cos(angle) ,0 ,sin(angle), 0));
    m.setColumn(1, Vec4(0 ,1 ,0 ,0));
    m.setColumn(2, Vec4(-sin(angle) , 0, cos(angle), 0));
    m.setColumn(3, Vec4(0, 0, 0, 1));
    return m;
};

Mat4 Transformations::rotateZ(double angle) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(cos(angle) , -sin(angle), 0, 0));
    m.setColumn(1, Vec4(0, 0, 0, 0));
    m.setColumn(2, Vec4(sin(angle) , cos(angle), 0, 0));
    m.setColumn(3, Vec4(0, 0, 0, 0));
    return m;
};

Mat4 Transformations::translate(double x, double y, double z) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(1, 0, 0, x));
    m.setColumn(1, Vec4(0, 1, 0, y));
    m.setColumn(2, Vec4(0, 0, 1, z));
    m.setColumn(3, Vec4(0, 0, 0, 1));

    return m;
};

// Mat4 Transformations::translate(Vec3 vector) {
//     return translate(vector.x, vector.y, vector.z);
// }

Mat4 Transformations::scale(double x, double y, double z) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(x, 0, 0, 0));
    m.setColumn(1, Vec4(0, y, 0, 0));
    m.setColumn(2, Vec4(0, 0, z, 0));
    m.setColumn(3, Vec4(0, 0, 0, 1));

    return m;
};

Mat4 Transformations::screw(double x, double y, double z) {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4( 0, -z,  y, 0));
    m.setColumn(1, Vec4( z,  0, -x, 0));
    m.setColumn(2, Vec4(-y,  x,  0, 0));
    m.setColumn(3, Vec4( 0,  0,  0, 1));
    return m;
};




Mat4 Transformations::rotateXAroundPoint(double angle, Vec3 center) {
    double x = center.x, y = center.y, z = center.z;
    return translate(x, y, z) * rotateX(angle) * translate(-x, -y, -z);
};

Mat4 Transformations::rotateYAroundPoint(double angle, Vec3 center) {
    double x = center.x, y = center.y, z = center.z;
    return translate(x, y, z) * rotateY(angle) * translate(-x, -y, -z);
};

Mat4 Transformations::rotateZAroundPoint(double angle, Vec3 center) {
    double x = center.x, y = center.y, z = center.z;
    return translate(x, y, z) * rotateZ(angle) * translate(-x, -y, -z);
};

Mat4 Transformations::scaleAroundPoint(double sx, double sy, double sz, Vec3 center) {
    double x = center.x, y = center.y, z = center.z;
    return translate(x, y, z) * scale(sx, sy, sz) * translate(-x, -y, -z);
};