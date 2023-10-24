#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include "spotlight.h"

const double PI  = 3.141592653589793238463;

SpotLight::SpotLight(Vec3 position_in, Vec3 intensity_in, Vec3 direction_in, double openingAngle_in) : Light(position_in, intensity_in){
    direction = direction_in.normalized();
    openingAngle = std::max(0.0, std::min(PI, openingAngle_in));
};

Vec3 SpotLight::getLVector(Vec3 incidentPosition) {
    return (position - incidentPosition);
};

double SpotLight::getIncidenceDistance(Vec3 incidentPosition) {
    return getLVector(incidentPosition).mag();
};

Vec3 SpotLight::calculateHitIntensity(SDL_Renderer* renderer, Ray * raycast) {
    Vec3 hitIntensity = Vec3(0,0,0);
    
    Vec3 i = intensity;

    Vec3 l = (this->position - raycast->contactPosition()).normalized();
    Vec3 n = raycast->contact_normal;
    Vec3 matr = raycast->contact_material.roughness;
    Vec3 mats = raycast->contact_material.specular;

    if (raycast->contact_material.texture != nullptr) {
        matr = raycast->contact_material.getDiffuseAtUV(renderer, raycast->contact_uv);
    }

    //spotlight specific
    double spotFactor = (l*(-1)).dot(direction);
    double cutoffFactor = cos(openingAngle/2.0);
    double spotMult = 0.0;
    if (spotFactor > cutoffFactor) {
        spotMult = (1.0 - (1.0 - spotFactor) * 1.0/(1.0 - cutoffFactor));
    } //else { //outside spot area
    //    spotMult = 0.0;
    //}
    
    double distanceDecayFactor = 1 / ((position - raycast->contact_position)).magSquared();
    
    double difFactor =  l.dot(n);//std::max(0.0, l.dot(n));
    Vec3 difIAtK = Vec3(i.x*matr.x, i.y*matr.y, i.z*matr.z);
    Vec3 diffuseIntensity = difIAtK * difFactor;
    diffuseIntensity = diffuseIntensity.clampedPositive() * distanceDecayFactor * spotMult;



    hitIntensity = hitIntensity + diffuseIntensity;

    Vec3 specIAtK = Vec3(i.x*mats.x, i.y*mats.y, i.z*mats.z);
    Vec3 r = l.reflect(n);
    Vec3 v = raycast->direction;
    double mExp = raycast->contact_material.hardness;
    double specFactor = pow(std::max(0.0, r.dot(v)),mExp);
    Vec3 specularIntensity = specIAtK * specFactor;
    specularIntensity = specularIntensity.clampedPositive() * distanceDecayFactor * spotMult;

    hitIntensity = hitIntensity + specularIntensity;

    return hitIntensity;
};