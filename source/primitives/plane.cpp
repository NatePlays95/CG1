#include "plane.h"
#include <iostream>
#include <cmath>

Plane::Plane(){};

Plane::Plane(Vec3 position_in, Vec3 normal_in) {
    position = position_in;
    normalDirection = normal_in.normalized();
};

void Plane::printToConsole() {
    std::cout << "I'm a Plane object, normal " << normalDirection.toString() << std::endl;
};

bool Plane::intersect(Ray& raycast) {
    
    double t;
    // t = ((position - raycast.position).dot(direction) / raycast.direction.dot(direction));

    double denominator = raycast.direction.dot(normalDirection);
    if (denominator == 0) return false;

    t = (position - raycast.position).dot(normalDirection) / denominator;
    Vec3 contactPos = raycast.position + raycast.direction*t;

    Vec3 normal = this->normalDirection;

    //find uv
    // Vec3 a = normal.cross(Vec3(1, 0, 0));
    // Vec3 b = normal.cross(Vec3(0, 1, 0));
    // Vec3 max_ab = a.magSquared() < b.magSquared() ? b : a;
    // Vec3 c = normal.cross(Vec3(0, 0, 1));
    // Vec3 uDir = (max_ab.magSquared() < c.magSquared() ? c : max_ab).normalized();
    // Vec3 vDir = normal.cross(uDir);
    double uMag = sqrt(normal.x*normal.x + normal.y*normal.y);
    Vec3 uDir = Vec3(normal.y/uMag, -normal.y/uMag, 0);
    Vec3 vDir = normal.cross(uDir);
    double uvScaling = 0.001;

    Vec3 uv = Vec3(uDir.dot(contactPos), vDir.dot(contactPos), 0)*uvScaling;

    return raycast.updateT(t, this->normalDirection, material, uv);
    // if (shouldUpdate) {
    //     raycast.contact_color = color;
    // }
    // return shouldUpdate;    
};