#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Era donde se almacena información para procesar la imagen
typedef struct Image_Data{
    u_int16_t width;
    u_int16_t height;
    u_int16_t **array;
}image_data;

//u_int16_t distance;
u_int32_t min;

// Función para cargar la imagen a un arreglo 2D
void load_image_to_array(char *image_to_open, FILE *output, image_data *data);
void create_distance_map(image_data *image, image_data *template, image_data *window, image_data *dist);
unsigned int compute_distance(image_data *template, image_data *window);
