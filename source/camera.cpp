#include "camera.h"

Camera::Camera(){
    //eye = new Ray();
};



Mat4 Camera::lookAt(Vec3 eye, Vec3 at, Vec3 up_direction) {
    position = eye;
    target = at;
    Vec3 up = at + up_direction;
    
    Vec3 I, J, K;
    
    K = (eye - at).normalized();
    Vec3 viewUp = up - eye;
    I = (viewUp.cross(K)).normalized();
    J = (K.cross(I)).normalized();

    i = I; j = J; k = K;
    return this->cameraToWorldMatrix();
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
    m.setColumn(3, Vec4(a, b, c, 1));

    return m;
}