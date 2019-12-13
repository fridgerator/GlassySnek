rm -rf libglassysnek.*
gcc -c -o libglassysnek.o main.c -I/usr/include/python3.6m
ar rcs libglassysnek.a libglassysnek.o
