
all: MS1 MS2 FS# TODO: Create MS1_assg, MS2_assg, FS_assg. Delete all intermediate object files 
	rm -f *.o
# Executables
MS1: MS1_assg.o color.o spheres.o vector.o # TODO: MS1_assg executable prerequisites 
	# TODO: MS1_assg executable recipe
	gcc -DMS1 -Wall -Werror -std=c99 MS1_assg.o color.o spheres.o vector.o -o MS1_assg -lm

	
MS2: MS2_assg.o color.o spheres.o vector.o # TODO ...
	gcc -DMS2 -Wall -Werror -std=c99 MS2_assg.o color.o spheres.o vector.o -o MS2_assg -lm

FS: FS_assg.o color.o spheres.o vector.o # TODO ...
	gcc -DFS -Wall -Werror -std=c99 FS_assg.o color.o spheres.o vector.o -o FS_assg -lm


# Object files
# TODO: Makefile rules to compile source files into object files
MS1_assg.o: src/assg.c
	gcc -DMS1 -c src/assg.c -o MS1_assg.o
	
MS2_assg.o: src/assg.c
	gcc -DMS2 -c src/assg.c -o MS2_assg.o

FS_assg.o: src/assg.c
	gcc -DFS -c src/assg.c -o FS_assg.o

color.o: src/color.c
	gcc -c src/color.c -o color.o

spheres.o: src/spheres.c
	gcc -c src/spheres.c -o spheres.o

vector.o: src/vector.c
	gcc -c src/vector.c -o vector.o

# Clean up object files and executable
clean:
	rm -f *.o MS1_assg MS2_assg FS_assg
