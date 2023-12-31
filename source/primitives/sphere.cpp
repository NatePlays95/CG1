#include <cmath>
#include <utility>
#include "sphere.h"
#include <iostream>

Sphere::Sphere(){};

Sphere::Sphere(Vec3 position_in, double radius_in) {
    position = position_in;
    radius = radius_in;
};

void Sphere::printToConsole() {
    std::cout << "I'm a Sphere object, position " << position.toString() << " radius " << radius << std::endl;
};

bool Sphere::intersect(Ray& raycast) {
    
    double fA = raycast.direction.magSquared(); // 1
    double fB = 2 * (raycast.position - position).dot(raycast.direction);
    double fC = (raycast.position - position).magSquared() - radius*radius;
    double fD = fB*fB - 4*fA*fC; //delta

    double t;
    if (fD < 0) return false; //nao existem raizes

    //existe pelo menos uma raiz => contato    
    if (fD == 0) { //raiz unica
        t = -fB/fA;
    } else {
        double t1 = (-fB + sqrt(fD)) / (2.0*fA);
        double t2 = (-fB - sqrt(fD)) / (2.0*fA);

        if (t1 > t2) std::swap(t1, t2);

        if (t1 < 0) {
            t1 = t2; // if t0 is negative, let's use t1 instead
            if (t1 < 0) return false; // both t0 and t1 are negative
        }
        t = t1;
    }

    Vec3 normal = (raycast.position + raycast.direction*t - position).normalized();

    //find contact position
    //TODO: move to raycast class later
    //return raycast.updateT(t, normal, color);
    return raycast.updateT(t, normal, material);
}