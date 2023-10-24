#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include "directionallight.h"

DirectionalLight::DirectionalLight(Vec3 position_in, Vec3 intensity_in, Vec3 direction_in) : Light(position_in, intensity_in){
    direction = direction_in.normalized();
};

Vec3 DirectionalLight::getLVector(Vec3 incidentPosition) {
    return direction*-1;
};

double DirectionalLight::getIncidenceDistance(Vec3 incidentPosition) {
    return 1000000000000;
};

Vec3 DirectionalLight::calculateHitIntensity(SDL_Renderer* renderer, Ray * raycast) {
    Vec3 hitIntensity = Vec3(0,0,0);
    
    Vec3 i = intensity;

    //Vec3 l = (this->position - raycast->contactPosition()).normalized();
    Vec3 l = direction * -1;
    Vec3 n = raycast->contact_normal;
    Vec3 matr = raycast->contact_material.roughness;
    Vec3 mats = raycast->contact_material.specular;

    if (raycast->contact_material.texture != nullptr) {
        matr = raycast->contact_material.getDiffuseAtUV(renderer, raycast->contact_uv);
    }
    
    // double distanceDecayFactor = 1 / ((position - raycast->contact_position)).magSquared();
    
    double difFactor =  l.dot(n);//std::max(0.0, l.dot(n));
    Vec3 difIAtK = Vec3(i.x*matr.x, i.y*matr.y, i.z*matr.z);
    Vec3 diffuseIntensity = difIAtK * difFactor;
    diffuseIntensity = diffuseIntensity.clampedPositive();

    hitIntensity = hitIntensity + diffuseIntensity;

    Vec3 specIAtK = Vec3(i.x*mats.x, i.y*mats.y, i.z*mats.z);
    Vec3 r = l.reflect(n);
    Vec3 v = raycast->direction;
    double mExp = raycast->contact_material.hardness;
    double specFactor = pow(std::max(0.0, r.dot(v)),mExp);
    Vec3 specularIntensity = specIAtK * specFactor;
    specularIntensity = specularIntensity.clampedPositive();

    hitIntensity = hitIntensity + specularIntensity;

    return hitIntensity;
};