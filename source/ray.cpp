#include "vec3.h"
#include "ray.h"

Ray::Ray(){};

//t
//contact position
//contact normal

Ray::Ray(Vec3 position_in){
    this->position = position_in;
    this->direction = Vec3(0,0,-1); //apontando pra frente
};

Ray::Ray(Vec3 position_in, Vec3 direction_in){
    this->position = position_in;
    this->direction = direction_in.normalized();
};

void Ray::pointTowards(Vec3 target) {
    this->direction = target - this->position;
    this->direction = this->direction.normalized();
};

bool Ray::update_t(double new_t) {
    if (new_t < 0) return false;
    if (new_t >= t) return false;

    t = new_t;
    contact_position = position + direction * t;
    return true;
}