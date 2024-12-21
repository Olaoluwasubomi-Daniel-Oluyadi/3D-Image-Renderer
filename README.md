# 3D-Image-Renderer
Ray Tracing Project README
This project implements a basic ray tracing program that simulates the rendering of 3D scenes. It reads input data such as sphere positions, colors, lighting parameters, and viewport settings from a file, and then renders the scene based on the ray tracing algorithm. This README provides detailed information about how to set up, run, and understand the project.

Table of Contents
Introduction
Requirements
File Structure
Setup Instructions
Running the Program
Input Format
Output Format
Functions and Implementation Details
Customization
Acknowledgments
Introduction
This project simulates a basic ray tracing system where rays are cast from a camera into a 3D world containing spheres. The program computes the color of each pixel based on the intersection of rays with objects, considering lighting effects such as diffuse reflection and shadows. The program supports multiple milestones, including a basic rendering (Milestone 1), a black-and-white scene rendering (Milestone 2), and full scene rendering with color and shadows (FS).

The ray tracing algorithm uses vector mathematics to compute intersections, lighting, and shading for each pixel in the output image.

Requirements
Before running the program, ensure that the following tools are available:

A C compiler (e.g., GCC)
The standard C library
The math.h library for mathematical operations
Makefile (optional, for easy compilation)
File Structure
The project consists of several source code files and header files. Below is the directory structure of the project:

bash
Copy code
/ray-tracing
│
├── assg.c           # Main source code file containing the ray tracing logic
├── assg.h           # Header file defining data structures (Camera, Viewport, Sphere, etc.)
├── color.c          # Contains functions for color manipulation
├── color.h          # Header file for color-related functions and structures
├── spheres.c        # Contains functions for sphere creation, intersection, and color
├── spheres.h        # Header file for sphere-related functions and structures
├── vector.c         # Contains vector mathematics functions (add, subtract, normalize, etc.)
├── vector.h         # Header file for vector-related functions and structures
├── Makefile (optional) # Makefile for compiling the project (optional)
└── README.md        # This file
Setup Instructions
1. Clone the repository
Clone the project repository to your local machine using the following command:

bash
Copy code
git clone <repository-url>
cd ray-tracing
2. Compile the project
You can compile the project manually or by using a Makefile (if provided). To compile manually using GCC, use the following command:

bash
Copy code
gcc -o ray-tracer assg.c color.c spheres.c vector.c -lm
Alternatively, if a Makefile is provided, you can simply run:

bash
Copy code
make
3. Check Dependencies
Make sure that your system has the necessary C compiler (GCC, Clang, etc.) and mathematical libraries (math.h), which are commonly available on most systems.

Running the Program
To run the ray tracing program, execute the compiled binary with two arguments:

bash
Copy code
./ray-tracer <input-file-path> <output-file-path>
<input-file-path>: Path to the input file containing the scene data.
<output-file-path>: Path where the rendered image will be saved.
Example:

bash
Copy code
./ray-tracer input.txt output.ppm
The program reads the input data from the specified file and writes the output (rendered image) to the specified file in the PPM (Portable Pixel Map) format.

Input Format
The input file contains the following data:

Width and Height of the image (int): Specifies the resolution of the output image.
Viewport height (float): The height of the camera's viewport.
Focal length (float): The distance from the camera to the viewport.
Light position (float x, float y, float z): The position of the light source in 3D space.
Light brightness (float): The intensity of the light.
Colors (hexadecimal): A list of colors used for spheres and background. Each color is specified in the form of a hexadecimal number.
Background color index (int): The index of the background color in the list of colors.
Spheres: A list of spheres, each defined by:
Position (float x, float y, float z)
Radius (float)
Color index (int): The index of the color for the sphere in the color list.
An example input file:

diff
Copy code
800 600
2.0
1.5
1.0 1.0 1.0 1.0
3
FF0000
00FF00
0000FF
0
2
1.0 1.0 -5.0 1.0 0
-1.0 -1.0 -5.0 1.0 1
Output Format
The output file is written in PPM format (P3 format), which is a simple and widely-used image format. The output consists of the following sections:

Header: "P3", followed by the width and height of the image, and the maximum color value (255).
Pixel data: Each pixel is represented by three values (RGB) in the range of 0 to 255.
Example:

kotlin
Copy code
P3
800 600
255
255 0 0 255 255 255 ... (pixel data)
Functions and Implementation Details
Main Program Flow
Initialization:
The worldInit function initializes the world, camera, and light parameters.
The readInput function reads scene data from the input file and stores it in the appropriate structures (camera, viewport, spheres, etc.).
Rendering:
The program uses a ray tracing algorithm to calculate the color of each pixel. Rays are cast from the camera's position into the scene, and their intersections with spheres are computed.
Lighting calculations (diffuse reflection and shadow checking) are applied to determine the final color for each pixel.
Milestone Support:
MS1: Basic vector operations and simple output.
MS2: Black-and-white rendering.
FS: Full rendering with lighting and shadows.
Key Functions
createCameraViewport: Initializes the camera and viewport settings.
calculateRayDirection: Computes the direction of a ray for a given pixel.
calculateLighting: Computes the color of a pixel based on lighting, considering diffuse reflection and distance-based attenuation.
isInShadow: Determines if a point is in shadow by checking if any objects block the light.
renderScene: Renders the entire scene by casting rays from the camera and calculating intersections with spheres.
Customization
You can customize the program in various ways:

Change the scene: Modify the input file to add or remove spheres, change light positions, and adjust colors.
Adjust the camera and viewport: Modify the camera's position, direction, and focal length in the Camera structure.
Experiment with lighting: Change the brightness of the light or modify the light's position.
