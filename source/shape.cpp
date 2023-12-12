#include "shape.h"
#include <iostream>

Shape::Shape(){};

//bool Shape::Shape(Ray raycast){ return false; };

void Shape::printToConsole() {
    std::cout << "I'm a base Shape object." << std::endl;
};

