#include <stdio.h>
#include <omp.h>
#include <climits>
#include "vec3.h"
#include "sphere.h"
#include "png.hpp"
#include <Windows.h>

Sphere sphereArray[5];
Sphere lightArray[1];
int sphereArrLen = 5;
int lightArrLen = 1;

Vec3 EyePosition = Vec3(960., 540., -100.); //eye position is in the center of the screen output
Vec3 LookAt = Vec3(0.,0.,0.); //look at origin

int setScene() {
    //spheres
    sphereArray[0] = Sphere(Vec3(100., 100., 0.), 40, Vec3(1., 0., 0.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[1] = Sphere(Vec3(1000., 600., 5.), 15, Vec3(0., 1., 0.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[2] = Sphere(Vec3(1600., 300., 10.), 35, Vec3(0., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[3] = Sphere(Vec3(800., 900., 20.), 60, Vec3(1., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[4] = Sphere(Vec3(1200., 500., 0.), 55, Vec3(1., 1., 0.), Vec3(0.5, 0.5, 0.5), false);

    //light
    lightArray[0] = Sphere(Vec3(960., 540., 50.), 1, Vec3(0., 0., 1.), Vec3(0.5, 0.5, 0.5), false);

    return 0;
}

png::rgb_pixel Trace(int i, int j) {

    Vec3 rayDirection = Vec3((float)i, (float)j, 0.) - EyePosition;
    rayDirection = rayDirection.Unit();

    Ray ray = Ray(EyePosition, rayDirection);
    Vec3 point;
    Vec3 normal;
    float minDistance = INFINITY;
    Sphere temp = Sphere();

    for (int k = 0; k < sphereArrLen; k++) {
	   if (sphereArray[k].Intersect(ray, point, normal)) {
		  float distance = (EyePosition - point).Length();
		  if (distance < minDistance) {
			 temp = sphereArray[k];
			 minDistance = distance;
		  }
	   }
    }

    if (!temp.getIsSet()) return png::rgb_pixel(0., 0., 0.);

    //see if temp sphere is valid
    Ray lightRay;
    lightRay.direction = lightArray[0].getCenter() - point;
    lightRay.origin = point;

    //compute shadows
    /*for (int k = 0; k < sphereArrLen; k++) {
	   if (sphereArray[k].Intersect(lightRay)) {
		  return png::rgb_pixel(0., 0., 0.);
	   }
    }*/

    Vec3 color = temp.getColor() * 255.f;
    /*if (color.x != 0. || color.y != 0. || color.z != 0.) {
	   printf("SUCCESS\n");
    }*/
    return png::rgb_pixel(color.x, color.y, color.z);

}

int main() {
    int imageWidth, imageHeight;
    double time0, time1;

    imageWidth = 1920;
    imageHeight = 1080;
    
    omp_set_num_threads(8);

    setScene();

    png::image<png::rgb_pixel> image(imageWidth, imageHeight);

    time0 = omp_get_wtime();

    #pragma omp parallel for
    for (int j = 0; j < imageHeight; j++) {
	   for (int i = 0; i < imageWidth; i++) {
		  image[j][i] = Trace(i, j);
	   }
    }

    time1 = omp_get_wtime();

    printf("TIME TAKEN %lf", (time1 - time0));
    
    image.write("rgb.png");
    Sleep(2000);
}