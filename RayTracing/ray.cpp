#include "ray.h"

Ray::Ray() { }

Ray::Ray(Vec3 o, Vec3 d) {
    this->origin = o;
    this->direction = d;
}