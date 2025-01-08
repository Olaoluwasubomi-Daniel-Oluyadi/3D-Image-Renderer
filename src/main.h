#include <stdio.h>
#include "color.h"
#include "spheres.h"
#include "vector.h"


#ifndef ASSG_H
#define ASSG_H




typedef struct {
    Vec3 position;       // Camera position in world coordinates (0,0,0)
    Vec3 direction;      // Always pointing in the -z direction
    float focalLength;   // Distance from the camera to the viewport
} Camera;

typedef struct {
    float width;         // Calculated to match the image aspect ratio
    float height;        // Given as input
    float z;             // z-coordinate of the viewport (-focalLength)
} Viewport;


typedef struct {
    Vec3 position;       // Position of the light in world coordinates
    float brightness;    // Brightness of the light source
} Light;

void readInput(const char *inputFile, World *world, Vec3 *backgroundColor, Vec3 *lightPosition, float *viewportWidth);
void print_milestone1_output(int i, Vec3 backgroundColor, Vec3 lightPosition, float viewportWidth, Sphere* spheres, int numSpheres);
void createCameraViewport(float viewportHeight, float aspectRatio, float focalLength);
Vec3 calculateRayDirection(int pixelX, int pixelY, int imageWidth, int imageHeight);
Vec3 calculateLighting(Vec3 intersection, Vec3 normal, Vec3 lightPos, float brightness, Vec3 sphereColor);
int isInShadow(Vec3 intersection, Vec3 normal, Vec3 lightPos, Sphere **spheres, int numSpheres);
void milestone2RenderScene(Sphere **spheres, int numSpheres, Vec3 lightPos, float brightness, int imgWidth, int imgHeight);
void FinalRenderScene(Sphere **spheres, int numSpheres, Vec3 lightPos, float brightness, int imgWidth, int imgHeight);
#endif