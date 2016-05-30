#include <stdio.h>
#include <omp.h>
#include <climits>
#include "vec3.h"
#include "sphere.h"

Sphere sphereArray[1];
Sphere lightArray[1];
int sphereArrLen = 1;
int lightArrLen = 1;

Vec3 EyePosition = Vec3(0., 0., -5.); //in the negative Z eye position
Vec3 LookAt = Vec3(0.,0.,0.); //look at origin

int setScene() {
    //spheres
    sphereArray[0] = Sphere(Vec3(0., 0., 0.), 2, Vec3(1., 0., 0.), Vec3(0.5, 0.5, 0.5), false);
    //objectArray[1] = Sphere(Vec3(0., 3., 0.), 2, Vec3(0., 1., 0.), Vec3(0.5, 0.5, 0.5), false);
    //light
    lightArray[0] = Sphere(Vec3(0., 3., 2.), 1, Vec3(0., 0., 1.), Vec3(0.5, 0.5, 0.5), false);

    return 0;
}

int main() {
    int imageWidth, imageHeight;

    imageWidth = imageHeight = 500;
    
    omp_set_num_threads(8);

    setScene();

    for (int i = 0; i < imageWidth; i++) {
	   for (int j = 0; j < imageHeight; j++) {
		  
		  Ray ray = Ray(EyePosition, Vec3(i, j, 0.));
		  Vec3 point;
		  Vec3 normal;
		  float minDistance = INFINITY;
		  Sphere temp = Sphere();

		  for (int k = 0; k < sphereArrLen; k++) {
			 if (sphereArray[k].Intersect(ray, &point, &normal)) {
				float distance = (EyePosition - point).Length();
				if (distance < minDistance) {
				    temp = sphereArray[k];
				    minDistance = distance;
				}
			 }
		  }


	   }
    }
    

}