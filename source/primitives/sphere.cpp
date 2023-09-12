#include <SDL2/SDL.h>
#include <cmath>
#include "sphere.h"

Sphere::Sphere(){};

Sphere::Sphere(Vec3 position_in, double radius_in) {
    position = position_in;
    radius = radius_in;
};

bool Sphere::intersect(Ray& raycast) {
    
    double fA = raycast.direction.magSquared(); // 1
    double fB = 2 * (raycast.position - position).dot(raycast.direction);
    double fC = (raycast.position - position).magSquared() - radius*radius;
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
        //TODO: move to raycast class later
        if (raycast.update_t(t)) raycast.contact_color = color;
        return true;
    }
}