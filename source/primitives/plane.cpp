#include <SDL2/SDL.h>
#include <cmath>
#include "plane.h"

Plane::Plane(){};

Plane::Plane(Vec3 position_in, Vec3 normal_in) {
    position = position_in;
    normalDirection = normal_in.normalized();
};

bool Plane::intersect(Ray& raycast) {
    
    double t;
    // t = ((position - raycast.position).dot(direction) / raycast.direction.dot(direction));

    double denominator = raycast.direction.dot(normalDirection);
    if (denominator == 0) return false;

    t = (position - raycast.position).dot(normalDirection) / denominator;

   
    // t = ((position.dot(direction) - raycast.position) / raycast.direction.dot(direction));
    Vec3 normal = this->normalDirection;

    return raycast.updateT(t, this->normalDirection, material);
    // if (shouldUpdate) {
    //     raycast.contact_color = color;
    // }
    // return shouldUpdate;    
};