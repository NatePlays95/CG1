#include <cmath>
#include <utility>
#include "conebody.h"

ConeBody::ConeBody(){};

ConeBody::ConeBody(Vec3 position_in, Vec3 direction_in, double radius_in, double height_in) {
    position = position_in;
    direction = direction_in.normalized();
    radius = radius_in;
    height = height_in;
};

bool ConeBody::intersect(Ray& raycast) {
    Vec3 v = position +  direction*height - raycast.position;
    Vec3 d = raycast.direction;
    Vec3 n = direction;

    double generatrix2 = height*height + radius*radius; //sqrt()^2
    double cos2theta = height*height / generatrix2; //cos2theta = (altura / geratriz)^2
    

    double fA = pow((d.dot(n)), 2) - (d.dot(d)) * cos2theta;
    double fB = (v.dot(d))*cos2theta - (v.dot(n))*(d.dot(n));
    double fC =pow((v.dot(n)), 2) - v.dot(v)*cos2theta;
    double fD = fB*fB - fA*fC; //delta

    
    if (fD < 0) return false;

    double t;
    //existe pelo menos uma raiz => contato    
    if (fD == 0) { //raiz unica
        t = -fB/fA;
    } else {
        double t1 = (-fB + sqrt(fD)) / (fA);
        double t2 = (-fB - sqrt(fD)) / (fA);
        
        if (t1 > t2) std::swap(t1, t2);

        if (t1 < 0) {
            t1 = t2; // if t0 is negative, let's use t1 instead
            if (t1 < 0) return false; // both t0 and t1 are negative
        }
        t = t1;
    }

    Vec3 contactPosition = raycast.position + raycast.direction*t;

    Vec3 contactProjection = (position - contactPosition).projectOnto(direction);

    if ((contactProjection + direction * height/2).magSquared() > height*height/4) return false;

    Vec3 contactToVertex = position + direction*height - contactPosition;
    Vec3 cross = (contactToVertex).cross(contactProjection - contactPosition);

    Vec3 normal = ((contactToVertex).cross(cross)).normalized();

    //find contact position
    return raycast.updateT(t, normal, material);
};