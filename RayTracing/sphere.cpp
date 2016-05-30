#include "sphere.h"

Sphere::Sphere() { }

Sphere::Sphere(Vec3 c, int r, Vec3 color, Vec3 light, bool isLight) {
    this->center = c;
    this->radius = r;
    this->color = color;
    this->lightProperties = light;
    this->isLight = isLight;
}

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

bool Sphere::isInsideSphere(Vec3 point, Sphere sphere) {
    Vec3 check = point - sphere.getCenter();
    float r = check.Length();
    return (r < sphere.getRadius());
}

bool Sphere::Intersect(Ray ray, Vec3 *point, Vec3 *normal) {
    int x = 5; 
    return true;
}

void Sphere::Print() {
    printf("Center Coordinates: %f, %f, %f\n", this->center.x, this->center.y, this->center.z);
    printf("Radius: %d\n", this->radius);
    printf("Sphere Color: %f, %f, %f\n", this->color.x, this->color.y, this->color.z);
    printf("Light Properties, Ambient: %f, Diffuse: %f, Specular: %f\n", this->lightProperties.x, this->lightProperties.y, this->lightProperties.z);
    printf("Is it a light: %d\n", this->isLight);
}