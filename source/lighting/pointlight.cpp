#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include "pointlight.h"

PointLight::PointLight(Vec3 position_in, Vec3 intensity_in) : Light(position_in, intensity_in){};

Vec3 PointLight::calculateDiffuseIntensity(Ray * raycast) {
    //Vec3 diffuseIntensity;
    
    // const Vec3 n = raycast->contact_normal;
    //Vec3 p = raycast->contact_position;
    Vec3 matr = raycast->contact_material.roughness;
    Vec3 l = (this->position - raycast->contactPosition()).normalized();
    Vec3 i = intensity;
    Vec3 n = raycast->contact_normal;
    
    double distanceDecayFactor = 1 / ((position - raycast->contact_position)).magSquared();
    double difFactor =  l.dot(n);//std::max(0.0, l.dot(n));

    Vec3 difIAtK = Vec3(i.x*matr.x, i.y*matr.y, i.z*matr.z);
    Vec3 diffuseIntensity = difIAtK * difFactor;
    diffuseIntensity = diffuseIntensity.clampedPositive() * distanceDecayFactor;

    return diffuseIntensity;
};

Vec3 PointLight::calculateSpecularIntensity(Ray * raycast) {
    //Vec3 specularIntensity;
    
    
    Vec3 matr = raycast->contact_material.roughness;
    Vec3 mats = raycast->contact_material.specular;
    Vec3 l = (this->position - raycast->contactPosition()).normalized();
    Vec3 i = intensity;
    Vec3 n = raycast->contact_normal;

    double distanceDecayFactor = 1 / ((position - raycast->contact_position)).magSquared();

    Vec3 specIAtK = Vec3(i.x*mats.x, i.y*mats.y, i.z*mats.z);
    Vec3 r = l.reflect(n);
    Vec3 v = raycast->direction;
    double mExp = raycast->contact_material.hardness;
    double specFactor = pow(std::max(0.0, r.dot(v)),mExp);
    Vec3 specularIntensity = specIAtK * specFactor;
    specularIntensity = specularIntensity.clampedPositive() * distanceDecayFactor;

    return specularIntensity;
};

Vec3 PointLight::calculateHitIntensity(Ray * raycast) {
    Vec3 hitIntensity = Vec3(0,0,0);
    
    Vec3 i = intensity;

    Vec3 l = (this->position - raycast->contactPosition()).normalized();
    Vec3 n = raycast->contact_normal;
    Vec3 matr = raycast->contact_material.roughness;
    Vec3 mats = raycast->contact_material.specular;
    
    double distanceDecayFactor = 1 / ((position - raycast->contact_position)).magSquared();
    
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