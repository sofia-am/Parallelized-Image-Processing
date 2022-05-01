#include <stdio.h>
#include <stdlib.h>

// Estructura donde se almacena información para procesar la imagen
struct image_data{
    int width;
    int height;
    int **array;
};

// Función para cargar la imagen a un arreglo 2D
void load_image_to_array(char *image_to_open, FILE *output, struct image_data data);