#include "spheres.h"
#include "vector.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>

void worldInit(World *world) {
    world->size = 0;
    world->capacity = 1;  // Start with a capacity of 1
    world->spheres = (Sphere **)malloc(world->capacity * sizeof(Sphere *));
    if (world->spheres == NULL) {
        fprintf(stderr, "Memory allocation failed for spheres array\n");
        exit(1);
    }
}
void freeWorld(World *world) {
    for (int i = 0; i < world->size; i++) {
        free(world->spheres[i]);  // Free each Sphere pointer
    }
    free(world->spheres);  // Free the array of Sphere pointers
    world->spheres = NULL;
    world->size = 0;
    world->capacity = 0;
}

void addSphere(World *world, Sphere *sphere){
    if (world->size == world->capacity) {
        world->capacity *= 2;  // Double the capacity
        world->spheres = (Sphere **)realloc(world->spheres, world->capacity * sizeof(Sphere *));
        if (world->spheres == NULL) {
            fprintf(stderr, "Memory reallocation failed for spheres array\n");
            exit(1);
        }
    }

    world->spheres[world->size] = sphere;  // Add sphere and increment size
    world->size += 1;

}

Sphere *createSphere(float radius, Vec3 position, Vec3 color){
    Sphere *sphere = (Sphere *)malloc(sizeof(Sphere));
    if (sphere == NULL) {
        fprintf(stderr, "Memory allocation failed for sphere\n");
        exit(1);
    }
    sphere->r = radius;
    sphere->pos = position;
    sphere->color = color;
    return sphere;
}

int doesIntersect(const Sphere *sphere, Vec3 rayPos, Vec3 rayDir, float *t){
        // Step 1: Compute the quadratic coefficients (a, b, c)
    Vec3 V = subtract(rayPos, sphere->pos); // V = rayPos - sphere posiiton
    float a = dot(rayDir, rayDir);        // a = dot(rayDir, rayDir)
    float b = 2 * dot(rayDir, V);         // b = 2 * dot(rayDir, V)
    float c = dot(V, V) - (sphere->r * sphere->r); // c = dot(V, V) - r^2

    // Step 2: Calculate the discriminant
    float discriminant = (b * b) - (4 * a * c);

    // Step 3: Check discriminant for intersection
    if (discriminant < 0) {
        // No intersection (complex roots)
        return 0;
    }

    // Step 4: Solve for t using the quadratic formula
    float sqrtDisc = sqrt(discriminant);
    float t1 = (-b - sqrtDisc) / (2 * a);
    float t2 = (-b + sqrtDisc) / (2 * a);

    // Step 5: Determine the valid intersection point
    if (t1 > 0 && t2 > 0) {
        *t = fmin(t1, t2); // Take the closer positive intersection
    } else if (t1 > 0) {
        *t = t1; // Only t1 is valid
    } else if (t2 > 0) {
        *t = t2; // Only t2 is valid
    } else {
        return 0; // Both intersections are behind the ray
    }

    // Intersection found
    return 1;
    
}