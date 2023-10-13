#ifndef ROTATION_H
#define ROTATION_H

#include "mat4.h"
#include <array>

class Rotations{
    public:
        static std::array<double, 16> rotacaoX(double x);
        static std::array<double, 16> rotacaoY(double x);
        static std::array<double, 16> rotacaoZ(double x);
};

#endif;