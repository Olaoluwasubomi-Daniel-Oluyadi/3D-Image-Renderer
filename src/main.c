#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "spheres.h"
#include "color.h"
#include "main.h"

 // Initialize variables to store input data
World world;
Camera camera;
Viewport viewport;
Light light;
int widthG, heightG, numColorsG, numSpheresG, backgroundColorIndexG;
float viewportHeightG, focalLengthG, lightBrightnessG;
Vec3 backgroundColor;


int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file path> <output file path>\n", argv[0]);
        return 1;
    }

    const char *inputFile = argv[1];
    const char *outputFile = argv[2];
    
    worldInit(&world);  // Assuming a function to initialize the World structure
    
    
    Vec3 lightPosition;
    float viewportWidth;
    
    // Read input from file
    readInput(inputFile, &world, &backgroundColor, &lightPosition, &viewportWidth);

    freopen(outputFile, "w", stdout);
   
    createCameraViewport(viewportHeightG, (float)widthG / heightG, focalLengthG);
    // For full scene rendering in color for Final submission
    #ifdef FS
        FinalRenderScene(world.spheres, world.size, lightPosition, lightBrightnessG, widthG, heightG);
    #endif
    // Close the output file stream
    fclose(stdout);


    // Clean up and free any allocated memory
    freeWorld(&world);  // Assuming a function to free World and its dynamically allocated contents

    return 0;
}

void readInput(const char *inputFile, World *world, Vec3 *backgroundColor, Vec3 *lightPosition, float *viewportWidth) {
    FILE *file = fopen(inputFile, "r");
    if (!file) {
        fprintf(stderr, "Error opening input file\n");
        exit(1);
    }

    // Read basic parameters
    fscanf(file, "%d %d", &widthG, &heightG);
    fscanf(file, "%f", &viewportHeightG);
    fscanf(file, "%f", &focalLengthG);
    fscanf(file, "%f %f %f %f", &lightPosition->x, &lightPosition->y, &lightPosition->z, &lightBrightnessG);
    
    // Read colors
    fscanf(file, "%d", &numColorsG);
    Vec3 *colors = malloc(numColorsG * sizeof(Vec3));
    unsigned int colorList[numColorsG];
    for (int i = 0; i < numColorsG; i++) {
        unsigned int hexColor;
        fscanf(file, "%x", &hexColor);
        colorList[i] = hexColor;
    }
    qsort(colorList,numColorsG, sizeof(int), compareColor);

    for (int i = 0; i < numColorsG; i++) {
        colors[i] = unpackRGB(colorList[i]); 
    }

    // Read background color index
    fscanf(file, "%d", &backgroundColorIndexG);
    *backgroundColor = colors[backgroundColorIndexG];

    // Read spheres
    fscanf(file, "%d", &numSpheresG);
    for (int i = 0; i < numSpheresG; i++) {
        Vec3 pos;
        float radius;
        int colorIndex;
        fscanf(file, "%f %f %f %f %d", &pos.x, &pos.y, &pos.z, &radius, &colorIndex);
        Vec3 sphereColor = colors[colorIndex];
        Sphere *sphere = createSphere(radius, pos, sphereColor);
        addSphere(world, sphere);
        
    }

    // Calculate viewport width based on aspect ratio
    *viewportWidth = viewportHeightG * ((float)widthG / heightG);

    // Clean up
    free(colors);
    fclose(file);
}



void createCameraViewport(float viewportHeight, float aspectRatio, float focalLength) {
    // Initialize camera
    camera.position = (Vec3){0.0f, 0.0f, 0.0f};
    camera.direction = (Vec3){0.0f, 0.0f, -1.0f}; // -z direction
    camera.focalLength = focalLength;

    // Initialize viewport
    viewport.height = viewportHeight;
    viewport.width = viewportHeight * aspectRatio;
    viewport.z = -focalLength;
}

Vec3 calculateRayDirection(int pixelX, int pixelY, int imageWidth, int imageHeight) {
    // Calculate the pixel's center coordinates in the viewport
    float viewportX = (pixelX + 0.5f) * (viewport.width / imageWidth) - (viewport.width / 2);
    float viewportY = (pixelY + 0.5f) * (viewport.height / imageHeight) - (viewport.height / 2);

    // Calculate the direction vector from the camera to the pixel on the viewport
    Vec3 pixelPositionInViewport = {viewportX, viewportY, viewport.z};
    Vec3 direction = subtract(pixelPositionInViewport, camera.position);
    return normalize(direction); // Normalize the direction vector
}

Vec3 calculateLighting(Vec3 intersection, Vec3 normal, Vec3 lightPos, float brightness, Vec3 sphereColor) {
    Vec3 lightDir = normalize(subtract(lightPos, intersection));
    float intensity = brightness * fmax(dot(lightDir, normal), 0.0) /
                      pow(distance(lightPos, intersection), 2.0);
    intensity = fmin(intensity, 1.0); // Clamp intensity to 1
    return scalarMultiply(intensity, sphereColor); // Final color scaled by intensity
}

int isInShadow(Vec3 intersection, Vec3 normal, Vec3 lightPos, Sphere **spheres, int numSpheres) {
    Vec3 shadowOrigin = add(intersection, scalarMultiply(0.001, normal)); // Offset to avoid precision issues
    Vec3 lightVector = subtract(lightPos, shadowOrigin);
    float lightDistance = length(lightVector);
    Vec3 shadowRay = normalize(lightVector);

    float t;
    for (int i = 0; i < numSpheres; i++) {
        if (doesIntersect(spheres[i], shadowOrigin, shadowRay, &t) && t < lightDistance) {
            return 1; // Intersection with another sphere before reaching the light
        }
    }
    return 0;
}

void FinalRenderScene(Sphere **spheres, int numSpheres, Vec3 lightPos, float brightness, int imgWidth, int imgHeight) {
    printf("P3\n%d %d\n255\n", imgWidth, imgHeight);

    for (int y = imgHeight - 1; y >= 0; y--) {
        for (int x = 0; x < imgWidth; x++) {

            Vec3 accumulatedColor = (Vec3){0.0, 0.0, 0.0};
            int sampleCount = 0;

            
            for (int sy = -1; sy <= 1; sy++) { // Anti-aliasing loop
                for (int sx = -1; sx <= 1; sx++) {
                    int sampleX = x + sx;
                    int sampleY = y + sy;

                    // Boundary check
                    if (sampleX < 0 || sampleX >= imgWidth || sampleY < 0 || sampleY >= imgHeight) {
                        continue;
                    }

                    Vec3 rayDirection = calculateRayDirection(sampleX , sampleY, imgWidth, imgHeight);
                    float closestT = INFINITY;
                    Sphere *closestSphere = NULL;

                    // Find the closest intersecting sphere
                    for (int i = 0; i < numSpheres; i++) {
                        float t;
                        if (doesIntersect(spheres[i], camera.position, rayDirection, &t) && t < closestT) {
                            closestT = t;
                            closestSphere = spheres[i];
                        }
                    }

                    Vec3 sampleColor = backgroundColor;
                    #ifndef FS
                        sampleColor = (Vec3){0, 0, 0}; // Default background color
                    #endif

                    // If a sphere is hit, calculate its color
                    if (closestSphere) {
                        Vec3 intersection = add(camera.position, scalarMultiply(closestT, rayDirection));
                        Vec3 normal = normalize(subtract(intersection, closestSphere->pos));
                        Vec3 surfaceColor = calculateLighting(intersection, normal, lightPos, brightness, closestSphere->color);

                        // Apply shadow factor if in shadow
                        if (isInShadow(intersection, normal, lightPos, spheres, numSpheres)) {
                            surfaceColor = scalarMultiply(0.1, surfaceColor); // Dim the color in shadow
                        }
                        sampleColor = surfaceColor;
                    }

                    // Accumulate sample color
                    accumulatedColor = add(accumulatedColor, sampleColor);
                    sampleCount++;
                }
            }

            // Average the accumulated color
            Vec3 finalColor = scalarDivide(accumulatedColor, sampleCount);
            writeColour(finalColor);
        }
    }
}


