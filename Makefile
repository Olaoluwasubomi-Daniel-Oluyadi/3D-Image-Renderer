scene: scene.o color.o spheres.o vector.o # TODO ...
	gcc -DFS -Wall -Werror -std=c99 scene.o color.o spheres.o vector.o -o scene -lm


# Makefile rules to compile source files into object files

scene.o: src/main.c
	gcc -DFS -c src/main.c -o scene.o

color.o: src/color.c
	gcc -c src/color.c -o color.o

spheres.o: src/spheres.c
	gcc -c src/spheres.c -o spheres.o

vector.o: src/vector.c
	gcc -c src/vector.c -o vector.o

# Clean up object files and executable
clean:
	rm -f *.o scene
