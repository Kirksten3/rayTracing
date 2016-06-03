//#include <stdio.h>
//#include <omp.h>
//#include <climits>
//#include "vec3.h"
//#include "sphere.h"
//#include "png.hpp"
//#include <Windows.h>
//
//Sphere sphereArray[5];
//Sphere lightArray[1];
//int sphereArrLen = 5;
//int lightArrLen = 1;
//
//Vec3 EyePosition = Vec3(960., 540., -100.); //eye position is in the center of the screen output
//Vec3 LookAt = Vec3(0.,0.,0.); //look at origin
//
//float mix(float a, float b, float mix) {
//    return b * mix + a * (1 - mix);
//}
//
//int setScene() {
//    //spheres
//    sphereArray[0] = Sphere(Vec3(100., 100., 0.), 40, Vec3(1., 0., 0.), Vec3(0.5, 0.5, 0.5), false);
//    sphereArray[1] = Sphere(Vec3(300., 600., 5.), 15, Vec3(0., 1., 0.), Vec3(0.5, 0.5, 0.5), false);
//    sphereArray[2] = Sphere(Vec3(500., 300., 10.), 35, Vec3(0., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
//    sphereArray[3] = Sphere(Vec3(800., 900., 20.), 60, Vec3(1., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
//    sphereArray[4] = Sphere(Vec3(950., 500., 0.), 55, Vec3(1., 1., 0.), Vec3(0.5, 0.5, 0.5), false);
//
//    //light
//    lightArray[0] = Sphere(Vec3(960., 540., 50.), 1, Vec3(0., 0., 1.), Vec3(0.5, 0.5, 0.5), false);
//
//    return 0;
//}
//
//Vec3 Trace(Ray r) {
//    Vec3 color = Vec3(0., 0., 0.);
//
//    return color;
//}
//
//png::rgb_pixel Trace(int i, int j) {
//
//    Vec3 rayDirection = Vec3((float)i, (float)j, 0.) - EyePosition;
//    rayDirection = rayDirection.Unit();
//
//    Ray ray = Ray(EyePosition, rayDirection);
//    Vec3 point;
//    Vec3 normal;
//    float minDistance = INFINITY;
//    Sphere temp = Sphere();
//
//    for (int k = 0; k < sphereArrLen; k++) {
//	   if (sphereArray[k].Intersect(ray, point, normal)) {
//		  float distance = (EyePosition - point).Length();
//		  if (distance < minDistance) {
//			 temp = sphereArray[k];
//			 minDistance = distance;
//		  }
//	   }
//    }
//
//    if (!temp.getIsSet()) return png::rgb_pixel(0., 0., 0.);
//
//    //see if temp sphere is valid
//    Ray lightRay;
//    lightRay.isLightRay = true;
//    lightRay.direction = lightArray[0].getCenter() - point;
//    lightRay.origin = point;
//
//    //run lightray through trace
//
//    //compute shadows
//    /*for (int k = 0; k < sphereArrLen; k++) {
//	   if (sphereArray[k].Intersect(lightRay)) {
//		  return png::rgb_pixel(0., 0., 0.);
//	   }
//    }*/
//
//    //diffuse calculation
//    Vec3 surfaceToLight = (lightArray[0].getCenter() - point).Unit();
//    float diffuseCoefficient = max(0.0, normal.Dot(surfaceToLight));
//    
//    Vec3 diffuse = (temp.getColor() * lightArray[0].getColor()) * diffuseCoefficient;
//    
//    //ambient
//    Vec3 ambient = (temp.getColor() * lightArray[0].getColor()) * temp.getLightProperties().x;
//
//    //specular calculation
//    Vec3 incidenceVector = surfaceToLight * -1.;
//    //angle of incidence = angle of reflection
//    Vec3 reflectionVector = incidenceVector - ((normal * 2) * incidenceVector.Dot(normal));
//    Vec3 surfaceToCamera = (EyePosition - point).Unit();
//    float cosAngle = max(0.0, surfaceToCamera.Dot(reflectionVector));
//    float specularCoefficient = pow(cosAngle, temp.getLightProperties().z);
//    Vec3 specular = temp.getColor() * specularCoefficient;
//
//    float distanceToLight = (lightArray[0].getCenter() - point).Length();
//    float attenuation = 1.0 / (1.0 + 0.1*distanceToLight * distanceToLight*distanceToLight);
//
//    Vec3 color = ambient + ((diffuse * specular) * attenuation);
//
//    color = color * 255.f;
//
//    //Vec3 color = temp.getColor() * 255.f;
//    /*if (color.x != 0. || color.y != 0. || color.z != 0.) {
//	   printf("SUCCESS\n");
//    }*/
//    return png::rgb_pixel(color.x, color.y, color.z);
//
//}
//
//int main() {
//    int imageWidth, imageHeight;
//    double time0, time1;
//    float invWidth, invHeight, fov, aspectratio, angle;
//
//    imageWidth = 1000;
//    imageHeight = 1000;
//    invWidth = 1. / (float)imageWidth;
//    invHeight = 1. / (float)imageHeight;
//    fov = 30;
//    aspectratio = imageWidth / (float)imageHeight;
//    angle = tan(M_PI * 0.5 * fov / 180.);
//
//    setScene();
//
//    png::image<png::rgb_pixel> image(imageWidth, imageHeight);
//    
//    //openMP stuff
//    omp_set_num_threads(8);
//
//    time0 = omp_get_wtime();
//
//    #pragma omp parallel for
//    for (int j = 0; j < imageHeight; j++) {
//	   for (int i = 0; i < imageWidth; i++) {
//		  float ii = (2 * ((i + 0.5) * invWidth) - 1) * angle * aspectratio;
//		  float jj = (1 - 2 * ((j + 0.5) * invHeight)) * angle;
//		  
//		  image[j][i] = Trace(i, j);
//	   }
//    }
//
//    time1 = omp_get_wtime();
//
//    printf("TIME TAKEN %lf", (time1 - time0));
//    
//    image.write("rgb.png");
//    Sleep(2000);
//}