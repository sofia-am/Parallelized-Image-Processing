#include "../inc/file_processing.h"

void load_image_to_array(char *image_to_open)
{
   // Variables
    FILE *imagen;
    FILE *output;
    char *nombre;
    char line[200];
    int x, y;
    image_data data;

    nombre = image_to_open;

    output = fopen("output.txt", "a");

    // Abro la imagen
    printf("Abriendo el archivo %s\n", nombre);
    imagen = fopen(nombre, "r");

    /*  Nos vamos moviendo entre las 3 primeras líneas
        ya que contiene algunos datos que no nos sirven:
        P2          -> header
        5745 3830   -> tamaño: ancho alto
        255         -> max pixel value
    */
    printf("Leyendo la información del header\n");
    fscanf(imagen, "%[^\n]\n", line);
    fscanf(imagen, "%d %d\n", &data.width, &data.height);
    fscanf(imagen, "%[^\n]\n", line);

    data.array = malloc((unsigned long)data.width*sizeof(int*));
    for(int i = 0 ; i < data.width ; i++)
        data.array[i] = malloc((unsigned long)data.height*sizeof(int));
  
    // Almaceno en un array de 2 dimensiones
    printf("Leyendo la imagen %s\n", nombre);
    x = 0;
    while(x < data.width)
    {
        y = 0;
        while(y < data.height)
        {
            fscanf(imagen, "%d", &data.array[x][y]);
            y++;
        }
        x++;
    }

    for(int i = 0; i<data.width; i++){
        for(int j = 0; j<data.height; j++){
            fprintf(output, "%d ",data.array[i][j]);
        }
        fprintf(output, "\n");
    }

    // Cerramos los files abiertos
    printf("Cerrando el archivo %s\n", nombre);
    fclose(imagen);
    fclose(output);
} 