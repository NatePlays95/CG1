#include "camera.h"
#include <cmath>

const double PI  = 3.141592653589793238463;

Camera::Camera(){
    //eye = new Ray();
};

Mat4 Camera::lookAt(Vec3 eye, Vec3 at, Vec3 up_direction) {
    position = eye;
    target = at;
    // Vec3 up = at + up_direction;
    
    // Vec3 I, J, K;
    
    // K = (eye - at).normalized();
    // Vec3 viewUp = up - eye;
    // I = (viewUp.cross(K)).normalized();
    // J = (K.cross(I)).normalized();

    // i = I; j = J; k = K;
    
    Vec3 forward, up, right;
    forward = (eye - at).normalized();
    right = (up_direction.cross(forward)).normalized();
    up = (forward.cross(right)).normalized();
    i = right; j = up; k = forward;

    return this->cameraToWorldMatrix();
};

void Camera::setFOV(double angleRadians) {
    // consider hfov and vfov the same, due to square window
    angleRadians = std::max(angleRadians, PI/18.0); //min fov: 10°
    angleRadians = std::min(angleRadians, 17*PI/18.0); //max fov: 170°

    double t = tan(angleRadians/2.0);
    // horizontal fov
    // w = d * tan(hfov/2) * 2
    this->frameWidth = 2 * frameDistance * t;
    // verical fov
    // h = d * tan(vfov/2) * 2
    this->frameHeight = 2 * frameDistance * t;
};

// Mat4 Camera::lookAt(Vec3 at) {
//     return lookAt(position, at, j);
// }

Mat4 Camera::cameraToWorldMatrix() {
    Mat4 m = Mat4();
    m.setColumn(0, Vec4(i, 0));
    m.setColumn(1, Vec4(j, 0));
    m.setColumn(2, Vec4(k, 0));

    double a = i.dot(position) * -1;
    double b = j.dot(position) * -1;
    double c = k.dot(position) * -1;
    // double a = -position.x;
    // double b = -position.y;
    // double c = -position.z;
    // m.setColumn(3, Vec4(a, b, c, 1));
    m.setColumn(3, Vec4(0,0,0,1));

    return m;
};

Mat4 Camera::worldToCameraMatrix() {
    Mat4 m = Mat4();
    double a = i.dot(position) * -1;
    double b = j.dot(position) * -1;
    double c = k.dot(position) * -1;

    m.setLine(0, Vec4(i, a));
    m.setLine(1, Vec4(j, b));
    m.setLine(2, Vec4(k, c));
    m.setLine(3, Vec4(0,0,0,1));

    return m;
};