#include <stdio.h>
#include <stdlib.h>

// Estructura donde se almacena información para procesar la imagen
struct image_data{
    u_int16_t width;
    u_int16_t height;
    u_int16_t **array;
};

u_int16_t distance;

// Función para cargar la imagen a un arreglo 2D
void load_image_to_array(char *image_to_open, FILE *output, struct image_data data);
void create_distance_map(struct image_data image, struct image_data template, struct image_data window, struct image_data dist);
void compute_distance(struct image_data template, struct image_data window);
