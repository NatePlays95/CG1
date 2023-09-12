#include <SDL2/SDL.h>
#include <cmath>
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

    double t;
    if (fD < 0) { //nao existem raizes
        return false;
    } else { //existe pelo menos uma raiz => contato    
        if (fD == 0) { //raiz unica
            t = -fB/fA;
        } else {
            double t1 = (-fB + sqrt(fD)) / (fA);
            double t2 = (-fB - sqrt(fD)) / (fA);
            
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

        //test if bounded by height
        Vec3 contactProjection = (position - raycast.position - raycast.direction*t).projectOnto(direction) + direction * height/2;
        //too tall
        if (contactProjection.magSquared() > height*height/4) return false;
        //going past the cylinder's bottom base
        // if (contactProjection.dot(direction) < 0) return false;

        //find contact position
        if (raycast.update_t(t)) raycast.contact_color = color;
        return true;
    }   
};