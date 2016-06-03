#include "vec3.h"

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    bool isLightRay;
    int depth;
    Ray();
    Ray(Vec3, Vec3);
};