#include "vec3.h"
#include "ray.h"

class Sphere {
public:
    Sphere();
    Sphere(Vec3, int, Vec3, Vec3, bool);
    Vec3 getCenter();
    int getRadius();
    Vec3 getColor();
    Vec3 getLightProperties();
    bool getIsLight();
    bool isInsideSphere(Vec3, Sphere);
    bool Intersect(Ray, Vec3*, Vec3*);
    void Print();

private:
    Vec3 center;
    int radius;
    Vec3 color;
    Vec3 lightProperties; //ka, kd, ks (ambient, diffuse, specular)
    bool isLight;
};