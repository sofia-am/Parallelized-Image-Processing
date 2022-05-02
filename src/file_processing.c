#include "../inc/file_processing.h"

void load_image_to_array(char *image_to_open, FILE *output, image_data *data)
{
    // Variables
    FILE *imagen;
    char line[200];
    int x, y;
    // Abro la imagen
    printf("Abriendo el archivo %s\n", image_to_open);
    imagen = fopen(image_to_open, "r");
    if (!imagen)
    {
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
    rewind(imagen);
    fscanf(imagen, "%[^\n]\n", line);
    fscanf(imagen, "%hu %hu\n", &data->width, &data->height);
    fscanf(imagen, "%[^\n]\n", line);

    data->array = malloc((size_t)data->width * sizeof(u_int16_t *));
    for (int i = 0; i < data->width; i++)
        data->array[i] = malloc((size_t)data->height * sizeof(u_int16_t));

    // Almaceno en un->array de 2 dimensiones
    printf("Procesando la imagen %s\n", image_to_open);
    x = 0;
    while (x < data->width)
    {
        y = 0;
        while (y < data->height)
        {
            fscanf(imagen, "%hu", &data->array[x][y]);
            fprintf(output, "%hu ", data->array[x][y]);
            y++;
        }
        fprintf(output, "\n");
        x++;
    }
    // Cerramos los files abiertos
    printf("Alto x Ancho: %hu %hu\n", data->width, data->height);

    printf("Cerrando el archivo %s\n", image_to_open);
    fclose(imagen);
    fclose(output);
}

void create_distance_map(image_data *image, image_data *template, image_data *window, image_data *dist)
{   
    u_int16_t distance;
    dist->height = (u_int16_t)(image->height - template->height);
    dist->width = (u_int16_t)(image->width - template->width);
    //printf("Entré ");
    // recorremos la imagen
    for (int i = 0; i < (image->width - template->width); i++)
    {
        for (int j = 0; j < (image->height - template->height); j++)
        {
            distance = 0;
            // armamos la ventana con el mismo tamaño del template
            for (int n = 0; n < (template->width); n++)
            {
                for (int m = 0; m < (template->height); m++)
                {
                    // creamos una ventana con los elementos de I
                    window->array[n][m] = image->array[n+i][m+j];
                }
            }
            // calculamos la distancia entre los pixeles de la ventana con los del template
            distance = compute_distance(template, window);
            dist->array[i][j] = distance;
        }
    }
}

u_int16_t compute_distance(image_data *template, image_data *window)
{   
    //u_int16_t distance;
    unsigned int sum = 0;
    u_int16_t aux = 0;
    u_int16_t max = 255;

    for (int i = 0; i < template->width; i++)
    {
        for (int j = 0; j < template->height; j++)
        {
            sum += (unsigned int)((template->array[i][j] - window->array[i][j]) * (template->array[i][j] - window->array[i][j]));
        }
    }
    unsigned int norm = (unsigned int)(max * max * template->height * template->height) / max;
    aux = (u_int16_t)(sum/norm);
    return aux;
}   