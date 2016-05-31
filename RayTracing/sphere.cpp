#include "sphere.h"
#include <algorithm>
#include <ctime>

Sphere::Sphere() { this->isSet = false; }

Sphere::Sphere(Vec3 c, int r, Vec3 color, Vec3 light, bool isLight) {
    this->center = c;
    this->radius = r;
    this->color = color;
    this->lightProperties = light;
    this->isLight = isLight;
    this->isSet = true;
}

//void Sphere::RandomSphere() {
//    Sphere newSphere;
//
//    srand(time(NULL));
//
//    float centerX = (float)(rand() % 1919);
//    float centerY = (float)(rand() % 1079);
//    float centerZ = 0.;
//
//    float radius = rand() % 20 + 15;
//    float colorR = ((float)(rand() % 254) / 255.);
//    float colorG = ((float)(rand() % 254) / 255.);
//    float colorB = ((float)(rand() % 254) / 255.);
//
//    Vec3 center = Vec3(centerX, centerY, centerZ);
//    this->center = center;
//    this->radius = radius;
//    Vec3 color = Vec3(colorR, colorG, colorB);
//    this->color = color;
//    this->isLight = false;
//    this->isSet = true;
//
//    this->Print();
//}

Vec3 Sphere::getCenter() {
    return this->center;
}

int Sphere::getRadius() {
    return this->radius;
}

Vec3 Sphere::getColor() {
    return this->color;
}

Vec3 Sphere::getLightProperties() {
    return this->lightProperties;
}

bool Sphere::getIsLight() {
    return this->isLight;
}

bool Sphere::getIsSet() {
    return this->isSet;
}

bool Sphere::isInsideSphere(Vec3 point, Sphere sphere) {
    Vec3 check = point - sphere.getCenter();
    float r = check.Length();
    return (r < sphere.getRadius());
}

bool Sphere::Intersect(Ray ray, Vec3 &point, Vec3 &normal) {
    Vec3 lVec = this->center - ray.origin;

    //distance from origin to center
    float tOC = lVec.Dot(ray.direction);
    
    //means direction and origin->center vector are opposite directions
    if (tOC < 0) return false;

    float d2 = lVec.Dot(lVec) - tOC * tOC;
    if (d2 > (this->radius * this->radius)) return false;

    /*float d = sqrtf(lVec.Length() * lVec.Length() - tOC * tOC);

    if (d < 0) return false;*/

    //distance from point on sphere to sphere center
    //float tPC = sqrtf(this->radius * this->radius - d * d);
    float tPC = sqrt(this->radius * this->radius - d2);
    float t0 = tOC - tPC;
    float t1 = tOC + tPC;

    //switch t0 and t1 as if t1 is less then it is closest
    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
	   t0 = t1;
	   if (t0 , 0) return false;
    }

    point = ray.origin + (ray.direction * t0);
    normal = (point - this->center).Unit();

    return true;
}

bool Sphere::Intersect(Ray ray) {
    Vec3 lVec = this->center - ray.origin;

    //distance from origin to center
    float tOC = lVec.Dot(ray.direction);
    
    //means direction and origin->center vector are opposite directions
    if (tOC < 0) return false;

    float d2 = lVec.Dot(lVec) - tOC * tOC;
    if (d2 > (this->radius * this->radius)) return false;

    /*float d = sqrtf(lVec.Length() * lVec.Length() - tOC * tOC);

    if (d < 0) return false;*/

    //distance from point on sphere to sphere center
    //float tPC = sqrtf(this->radius * this->radius - d * d);
    float tPC = sqrt(this->radius * this->radius - d2);
    float t0 = tOC - tPC;
    float t1 = tOC + tPC;

    //switch t0 and t1 as if t1 is less then it is closest
    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
	   t0 = t1;
	   if (t0 , 0) return false;
    }

    return true;
}

void Sphere::Print() {
    printf("Center Coordinates: %f, %f, %f\n", this->center.x, this->center.y, this->center.z);
    printf("Radius: %d\n", this->radius);
    printf("Sphere Color: %f, %f, %f\n", this->color.x, this->color.y, this->color.z);
    printf("Light Properties, Ambient: %f, Diffuse: %f, Specular: %f\n", this->lightProperties.x, this->lightProperties.y, this->lightProperties.z);
    printf("Is it a light: %d\n", this->isLight);
}