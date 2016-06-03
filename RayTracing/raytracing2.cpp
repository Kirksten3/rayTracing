#include <stdio.h>
#include <omp.h>
#include <climits>
#include "vec3.h"
#include "sphere.h"
#include "png.hpp"
#include <Windows.h>

Sphere sphereArray[2];
Sphere lightArray[1];
int sphereArrLen = 2;
int lightArrLen = 1;

Vec3 EyePosition = Vec3(0., 0., -10.); //eye position is in the center of the screen output
Vec3 LookAt = Vec3(0.,0.,0.); //look at origin

//mix individual values
float mix(float a, float b, float i) {
    return b * i + a * (1 - i);
}

//color mixer
Vec3 mix(Vec3 a, Vec3 b, float i) {
    Vec3 output = Vec3(mix(a.x, b.x, i), mix(a.y, b.y, i), mix(a.z, b.z, i));
    return output;
}

int setScene() {
    //spheres
    sphereArray[0] = Sphere(Vec3(0., 0., 10.), 5, Vec3(1., 0., 0.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[1] = Sphere(Vec3(3., 3., 5.), 3, Vec3(0., 1., 0.), Vec3(0.5, 0.5, 0.5), false);
    /*sphereArray[1] = Sphere(Vec3(300., 600., 5.), 15, Vec3(0., 1., 0.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[2] = Sphere(Vec3(500., 300., 10.), 35, Vec3(0., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[3] = Sphere(Vec3(800., 900., 20.), 60, Vec3(1., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
    sphereArray[4] = Sphere(Vec3(950., 500., 0.), 55, Vec3(1., 1., 0.), Vec3(0.5, 0.5, 0.5), false);*/

    //light
    lightArray[0] = Sphere(Vec3(-3., 0., 10.), 1, Vec3(1., 1., 1.), Vec3(0.5, 0.5, 0.5), false);

    return 0;
}

Vec3 Trace(Ray ray) {
    Vec3 color, lightColor;
    //check ray between objects
    Vec3 point, normal;
    Sphere temp = Sphere();
    float tNear = INFINITY;
    float t0;

    for (int k = 0; k < sphereArrLen; k++) {
	   if (sphereArray[k].Intersect2(ray, t0, point, normal)) {
		  if (t0 < tNear) {
			 tNear = t0;
			 temp = sphereArray[k];
		  }
	   }
    }

    if (!temp.getIsSet()) return Vec3(0.,0.,0.);

    else {
	   if (ray.direction.Dot(normal) > 0) normal = -normal;
	   //if (ray.depth < 5) {
		  //float facingRatio = -ray.direction.Dot(normal);
		  //float fresnelEffect = mix(pow(1 - facingRatio, 3), 1., 0.1);

		  //Vec3 reflectionDir = ray.direction - (normal * 2 * ray.direction.Dot(normal));
		  //reflectionDir = reflectionDir.Unit();

		  //Ray reflectionRay = Ray(point, reflectionDir);

		  ////increment depth
		  //reflectionRay.depth = ray.depth + 1;

		  //Vec3 reflection = Trace(reflectionRay);
		  //
		  //color = reflection * fresnelEffect * temp.getColor();
		  ////color = temp.getColor();
		  ////color = mix(color, lightColor, .1);
	   //}

	   else {
		  for (int i = 0; i < lightArrLen; i++) {
			 float transmission = 1.;
			 Vec3 lightDirection = lightArray[i].getCenter() - point;
			 lightDirection = lightDirection.Unit();

			 Ray lightRay = Ray(point, lightDirection);

			 for (int j = 0; j < sphereArrLen; j++) {
				if (sphereArray[j].Intersect2(lightRay)) {
				    transmission = 0.;
				    break;
				}
			 }
			 color = color + (temp.getColor() * transmission * max(0., normal.Dot(lightDirection)) * lightArray[i].getColor());
			 //color = mix(color, color2, 1.);
		  }
	   }
    }

    return color + temp.getColor();
}

int main() {
    double time0, time1;
    Vec3 color = Vec3(0., 0., 0.);
    int width, height;
    float areaWidth, areaHeight, xleft, ytop;
    width = 1024;
    height = 768;
    areaWidth = 48.;
    areaHeight = 36.;
    xleft = -1 * (areaWidth / 2.);
    ytop = areaHeight / 2.;
    float dx = areaWidth / (float)width;
    float dy = areaHeight / (float)height;

    setScene();

    png::image<png::rgb_pixel> image(width, height);

    //openMP stuff
    omp_set_num_threads(8);

    time0 = omp_get_wtime();

    #pragma omp parallel for
    for (int y = 0; y < height; ++y) {
	   for (int x = 0; x < width; ++x) {
		  //float medx = (0.5 * dx) + ((float)x * dx);
		  float xp = xleft + (0.5 * dx) + ((float)x * dx);
		  //float medy = (0.5 * dy) + ((float)y * dy);
		  float yp = ytop - ((0.5 * dy) + ((float)y * dy));
		  //Vec3 rDir, rOrig;
		  Vec3 rDir = Vec3((float)xp, (float)yp, 0.) - EyePosition;
		  rDir = rDir.Unit();
		  Vec3 rOrig = EyePosition;
		  Ray ray = Ray(rOrig, rDir);
		  color = Trace(ray);
		  color = color * 255.;
		  /*if (color.x != 0.) {
			 printf("Success at %d, %d\n", x, y);
		  }*/
		  image[y][x] = png::rgb_pixel(color.x, color.y, color.z);
	   }
    }

    time1 = omp_get_wtime();

    printf("TIME TAKEN %lf", (time1 - time0));
    
    image.write("rgb.png");
    //Sleep(10000);
}