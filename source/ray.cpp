#include "vec3.h"
#include "ray.h"

//Ray::Ray(){};

//t
//contact position
//contact normal

// Ray::Ray(Vec3 position_in){
//     this->position = position_in;
//     this->direction = Vec3(0,0,-1); //apontando pra frente
//     this->contact_color = {0,0,0,0};
// };

Ray::Ray(Vec3 position_in, Vec3 direction_in){
    this->position = position_in;
    this->direction = direction_in.normalized();
    this->contact_color = {0,0,0,0};
};

void Ray::pointTowards(Vec3 target) {
    this->direction = target - this->position;
    this->direction = this->direction.normalized();
};

//delete later
// bool Ray::update_t(double new_t) {
//     if (new_t < 0) return false;
//     if (new_t >= t) return false;

//     t = new_t;
//     contact_position = position + direction * t;
//     return true;
// }

Vec3 Ray::contactPosition() {
    return position + direction*t;
}

//TODO: delete later
bool Ray::updateT(double new_t, Vec3 new_normal, SDL_Color new_color) {
    if (new_t < 0) return false;
    if (new_t >= t) return false;

    t = new_t;
    contact_normal = new_normal;
    contact_color = new_color;
    return true;
}

bool Ray::updateT(double new_t, Vec3 new_normal, Material new_material) {
    if (new_t < 0) return false;
    if (new_t >= t) return false;

    t = new_t;
    contact_normal = new_normal;
    contact_material = new_material;
    return true;
}