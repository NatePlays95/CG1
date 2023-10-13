#include "rotations.h"
#include <cmath> 

std::array<double, 16> Rotations::rotacaoX(double x) {
    return {
         1, 0, 0, 0,
         cos(x), -sin(x), 0, 0,
         0, sin(x), cos(x), 0,
         0, 0, 0, 1
         };
}

std::array<double, 16> Rotations::rotacaoY(double x) {
    return {
         cos(x) ,0 ,sin(x), 0,
         0 ,1 ,0 ,0 ,
         -sin(x) , 0, cos(x), 0,
         0, 0, 0, 1
         };
}

std::array<double, 16> Rotations::rotacaoZ(double x) {
    return {
         cos(x) , -sin(x), 0, 0,
         0, 0, 0, 0,
         sin(x) , cos(x), 0, 0,
         0, 0, 0, 0
         };
}