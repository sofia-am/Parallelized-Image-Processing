#include "../inc/file_processing.h"

void load_image_to_array(char *image_to_open, FILE *output, struct image_data data)
{
   // Variables
    FILE *imagen;
    char *nombre;
    char line[200];
    int x, y;

    nombre = image_to_open;
    //char *string = calloc(40, sizeof(char));
    //sprintf(string, "[%s]output.txt", image_to_open);

    // Abro la imagen
    printf("Abriendo el archivo %s\n", nombre);
    imagen = fopen(nombre, "r");
    if(!imagen){
        perror("Error al abrir la imagen");
        exit(EXIT_FAILURE);
    }

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
    printf("Procesando la imagen %s\n", nombre);
    x = 0;
    while(x < data.width)
    {
        y = 0;
        while(y < data.height)
        {
            fscanf(imagen, "%d", &data.array[x][y]);
            fprintf(output, "%d ", data.array[x][y]);
            y++;
        }
        fprintf(output, "\n");
        x++;
    }
    // Cerramos los files abiertos
    printf("Cerrando el archivo %s\n", nombre);
    fclose(imagen);
    fclose(output);
} 

image_data create_distance_map(image_data image, image_data template, image_data window){

    for(int i = 0; i < (image.width - template.width); i++){
        for(int j = 0; j < (image.height - template.height); j++){
            for(int n = i; n < (template.width + i); n++){
                for(int m = j; m < (template.height + j); m++){
                    window.array[n][m] = image.array[n][m];

                }
            }
        }
    }
}

void compute_distance(image_data template, image_data window){
    int sum;
    for(int i = 0; i < template.width; i++){
        for(int j = 0; j < template.height; j++){
            sum += (template.array[i][j] - window.array[i][j]) * (template.array[i][j] - window.array[i][j]);
        }
    }
    int norm = (255*255*template.height*template.height)/255;

    distance = sum/norm;
}