#include "color.h"


int compareColor(const void *a, const void *b)
{
    int a1 = 0, b1 = 0;
    for (int i = 0; i < sizeof(int); i++)
    {
        a1 |= (*((unsigned char*)a + i) & 0x0F) << (i * 8);
        b1 |= (*((unsigned char*)b + i) & 0x0F) << (i * 8);
    }
    
    return (a1 < b1) ? -1 : (b1 < a1) ? 1 : (*((int*)a) < *((int*)b)) ? -1 : (*((int*)a) > *((int*)b)) ? 1 : 0;
}

Vec3 unpackRGB(unsigned int packedRGB) {
    Vec3 color;

    // Extract each channel and normalize to the [0, 1] range
    color.x = ((packedRGB >> 16) & 0xFF) / 255.0f;  // Red
    color.y = ((packedRGB >> 8) & 0xFF) / 255.0f;   // Green
    color.z = (packedRGB & 0xFF) / 255.0f;          // Blue

    return color;
}

void writeColour(Vec3 color) {
    int r = (int)(color.x * 255);
    int g = (int)(color.y * 255);
    int b = (int)(color.z * 255);
    printf("%d %d %d\n", r, g, b);
}
