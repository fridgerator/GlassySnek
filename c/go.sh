PY_INCLUDE_PATH=$(python-config --cflags)
rm -rf libglassysnek.*
gcc -c -o libglassysnek.o main.c -I$PY_INCLUDE_PATH
ar rcs libglassysnek.a libglassysnek.o
