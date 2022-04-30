#include <stdio.h>
#include <stdlib.h>

// Estructura donde se almacena información para procesar la imagen
typedef struct {
    int width;
    int height;
    int **array;
} image_data;

// Función para cargar la imagen a un arreglo 2D
void load_image_to_array(char *image_to_open);