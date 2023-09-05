#include <SDL2/SDL.h>
#include <cmath>
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
    if (fD < 0) { //nao existem raizes
        return false;
    } else { //existe pelo menos uma raiz => contato    
        if (fD == 0) { //raiz unica
            t = -fB/fA;
        } else {
            double t1 = (-fB + sqrt(fD)) / (2*fA);
            double t2 = (-fB - sqrt(fD)) / (2*fA);
            
            if (t1 < t2) {
                if (t1 >= 0) t = t1;
                else if (t2 >= 0) t = t2;
                else return false;
            } else {
                if (t2 >= 0) t = t2;
                else if (t1 >= 0) t = t1;
                else return false;
            }
        }
        //find contact position
        if (raycast.update_t(t)) raycast.contact_color = color;
        return true;
    }   
};