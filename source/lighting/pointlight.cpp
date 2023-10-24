#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include "pointlight.h"

PointLight::PointLight(Vec3 position_in, Vec3 intensity_in) : Light(position_in, intensity_in){};


Vec3 PointLight::getLVector(Vec3 incidentPosition) {
    return (position - incidentPosition);
};

double PointLight::getIncidenceDistance(Vec3 incidentPosition) {
    return getLVector(incidentPosition).mag();
};


Vec3 PointLight::calculateHitIntensity(SDL_Renderer* renderer, Ray * raycast) {
    Vec3 i = intensity;
    Vec3 hitIntensity = Vec3(0,0,0);

    //TODO: skip objects if light is too distant for light to influence
    double distanceDecayPower = (position - raycast->contact_position).magSquared();
    // if (distanceDecayPower > intensity.mag()*0.05) return hitIntensity;
    
    //resume as usual
    Vec3 l = (this->position - raycast->contactPosition()).normalized();
    Vec3 n = raycast->contact_normal;
    Vec3 matr = raycast->contact_material.roughness;
    Vec3 mats = raycast->contact_material.specular;

    if (raycast->contact_material.texture != nullptr) {
        matr = raycast->contact_material.getDiffuseAtUV(renderer, raycast->contact_uv);
    }

    double distanceDecayFactor = 1 / distanceDecayPower;
    
    double difFactor =  l.dot(n);//std::max(0.0, l.dot(n));
    Vec3 difIAtK = Vec3(i.x*matr.x, i.y*matr.y, i.z*matr.z);
    Vec3 diffuseIntensity = difIAtK * difFactor;
    diffuseIntensity = diffuseIntensity.clampedPositive() * distanceDecayFactor;

    hitIntensity = hitIntensity + diffuseIntensity;

    Vec3 specIAtK = Vec3(i.x*mats.x, i.y*mats.y, i.z*mats.z);
    Vec3 r = l.reflect(n);
    Vec3 v = raycast->direction;
    double mExp = raycast->contact_material.hardness;
    double specFactor = pow(std::max(0.0, r.dot(v)),mExp);
    Vec3 specularIntensity = specIAtK * specFactor;
    specularIntensity = specularIntensity.clampedPositive() * distanceDecayFactor;

    hitIntensity = hitIntensity + specularIntensity;

    return hitIntensity;
};