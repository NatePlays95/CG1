#include <SDL2/SDL.h>
#include <cmath>
#include "disk.h"

Disk::Disk(){};

Disk::Disk(Vec3 position_in, Vec3 normal_in, double radius_in) {
    position = position_in;
    normalDirection = normal_in.normalized();
    radius = radius_in;
};

bool Disk::intersect(Ray& raycast) {
    
    double t;


    double denominator = raycast.direction.dot(normalDirection);
    if (denominator == 0) return false;
    t = (position - raycast.position).dot(normalDirection) / denominator;

    Vec3 contact_position = raycast.position + raycast.direction * t;
    if ((contact_position - position).lengthSquared() > radius*radius) return false;
    
    bool shouldUpdate = raycast.update_t(t);
    if (shouldUpdate) {
        raycast.contact_color = color;
    }
    return shouldUpdate;    
};