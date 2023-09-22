#include <SDL2/SDL.h>
#include "mat4.h"


Mat4::Mat4(){}

Mat4::Mat4(Mat4& source) {
    for (int i = 0; i < 16; i++){
        mat[i] = source.mat[i];
    }
}



Mat4 Mat4::operator + (const Mat4& obj) {
    Mat4 temp = Mat4();
    for (int i = 0; i < 16; i++){
        temp.mat[i] = mat[i] + obj.mat[i];
    }
    return temp;
}

Mat4 Mat4::operator - (const Mat4& obj) {
    Mat4 temp = Mat4();
    for (int i = 0; i < 16; i++){
        temp.mat[i] = mat[i] - obj.mat[i];
    }
    return temp;
}

Mat4 Mat4::operator * (double factor) {
    Mat4 temp = Mat4();
    for (int i = 0; i < 16; i++){
        temp.mat[i] = mat[i] * factor;
    }
    return temp;
}

Mat4 Mat4::operator / (double factor) {
    Mat4 temp = Mat4();
    for (int i = 0; i < 16; i++){
        temp.mat[i] = mat[i] / factor;
    }
    return temp;
}


Vec4 Mat4::operator * (const Vec4& v) {
    Vec4 temp = Vec4();
    temp.x = mat[0]*v.x + mat[4]*v.y +  mat[8]*v.z + mat[12]*v.w;
    temp.y = mat[1]*v.x + mat[5]*v.y +  mat[9]*v.z + mat[13]*v.w;
    temp.z = mat[2]*v.x + mat[6]*v.y + mat[10]*v.z + mat[14]*v.w;
    temp.w = mat[3]*v.x + mat[7]*v.y + mat[11]*v.z + mat[15]*v.w;
    return temp;
}

Mat4 Mat4::operator * (Mat4& with) {
    Mat4 temp = Mat4();
    for (int c = 0; c < 4; c++){
    for (int l = 0; l < 4; l++){
        double sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += at(l, i) * with.at(i, c);
        }
        temp.set(l, c, sum);
    }
    }
    return temp;
}






double Mat4::at(int l, int c) {
    return mat.at(c*4 + l);
}

Mat4* Mat4::set(int l, int c, double value) {
    mat[c*4 + l] = value;
    return this;
}

Mat4 Mat4::setLine(int l, const Vec4& vector) {
    mat[l] = vector.x;
    mat[l+4] = vector.y;
    mat[l+8] = vector.z;
    mat[l+12] = vector.w;
    return *this;
}

Mat4 Mat4::setColumn(int c, const Vec4& vector) {
    int c4 = c*4;
    mat[c4] = vector.x;
    mat[c4+1] = vector.y;
    mat[c4+2] = vector.z;
    mat[c4+3] = vector.w;
    return *this;
}


Mat4 Mat4::scaleMatrix(double sx, double sy, double sz) {
    Mat4* temp = new Mat4();
    temp = temp->set(0,0,sx)->set(1,1,sy)->set(2,2,sz)->set(3,3,1);
    return *temp;
}