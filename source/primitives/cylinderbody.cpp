#include <cmath>
#include <utility>
#include "cylinderbody.h"

CylinderBody::CylinderBody(){};

CylinderBody::CylinderBody(Vec3 position_in, Vec3 direction_in, double radius_in, double height_in) {
    position = position_in;
    direction = direction_in.normalized();
    radius = radius_in;
    height = height_in;
};

bool CylinderBody::intersect(Ray& raycast) {
    Vec3 v = (raycast.position - position) - direction * (direction.dot(raycast.position - position));
    Vec3 w = raycast.direction - direction * (direction.dot(raycast.direction));

    double fA = w.dot(w);
    double fB = 2 * v.dot(w);
    double fC =(v.dot(v) - radius*radius);
    double fD = fB*fB - 4*fA*fC; //delta

    double t;
    if (fD < 0) return false;
        
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

    //test if bounded by height
    Vec3 contactPosition = raycast.position + raycast.direction*t;
    Vec3 contactProjectionLength = (contactPosition - position).projectOnto(direction);
    //too tall
    if (contactProjectionLength.magSquared() > height*height/4.0) return false;
    //going past the cylinder's bottom base
    // if (contactProjection.dot(direction) < 0) return false;

    Vec3 contactProjectionPoint = position + contactProjectionLength;
    Vec3 normal = (contactPosition - contactProjectionPoint).normalized();

    return raycast.updateT(t, normal, material);
};