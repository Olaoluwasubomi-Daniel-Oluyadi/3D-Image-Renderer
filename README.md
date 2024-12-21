# Ray Tracing Project README

This project implements a basic ray tracing program that simulates the rendering of 3D scenes. It reads input data such as sphere positions, colors, lighting parameters, and viewport settings from a file, and then renders the scene based on the ray tracing algorithm. This README provides detailed information about how to set up, run, and understand the project.

## Table of Contents
1. [Introduction](#introduction)
2. [Requirements](#requirements)
3. [File Structure](#file-structure)
4. [Setup Instructions](#setup-instructions)
5. [Running the Program](#running-the-program)
6. [Input Format](#input-format)
7. [Output Format](#output-format)
8. [Functions and Implementation Details](#functions-and-implementation-details)
9. [Customization](#customization)
10. [Acknowledgments](#acknowledgments)

## Introduction
This project simulates a basic ray tracing system where rays are cast from a camera into a 3D world containing spheres. The program computes the color of each pixel based on the intersection of rays with objects, considering lighting effects such as diffuse reflection and shadows. The program supports multiple milestones, including a basic rendering (Milestone 1), a black-and-white scene rendering (Milestone 2), and full scene rendering with color and shadows (FS).

The ray tracing algorithm uses vector mathematics to compute intersections, lighting, and shading for each pixel in the output image.

## Requirements
Before running the program, ensure that the following tools are available:
- A C compiler (e.g., GCC)
- The standard C library
- The `math.h` library for mathematical operations
- Makefile (optional, for easy compilation)

## File Structure
The project consists of several source code files and header files. Below is the directory structure of the project:

