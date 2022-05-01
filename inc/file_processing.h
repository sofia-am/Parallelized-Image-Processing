#include <stdio.h>
#include <stdlib.h>

// Estructura donde se almacena información para procesar la imagen
typedef struct image_data{
    int width;
    int height;
    int **array;
}image_data;

int distance;

// Función para cargar la imagen a un arreglo 2D
void load_image_to_array(char *image_to_open, FILE *output, image_data data);
image_data create_distance_map(image_data image, image_data template, image_data window);
void compute_distance(image_data template, image_data image);