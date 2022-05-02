#include "../inc/file_processing.h"

void load_image_to_array(char *image_to_open, FILE *output, struct image_data data)
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
    fscanf(imagen, "%d %d\n", &data.width, &data.height);
    fscanf(imagen, "%[^\n]\n", line);

    data.array = malloc((size_t)data.width * sizeof(u_int16_t *));
    for (int i = 0; i < data.width; i++)
        data.array[i] = malloc((size_t)data.height * sizeof(u_int16_t));

    // Almaceno en un array de 2 dimensiones
    printf("Procesando la imagen %s\n", image_to_open);
    x = 0;
    while (x < data.width)
    {
        y = 0;
        while (y < data.height)
        {
            fscanf(imagen, "%d", &data.array[x][y]);
            fprintf(output, "%d ", data.array[x][y]);
            y++;
        }
        fprintf(output, "\n");
        x++;
    }
    // Cerramos los files abiertos
    printf("Alto x Ancho: %d %d\n", data.width, data.height);

    printf("Cerrando el archivo %s\n", image_to_open);
    fclose(imagen);
    fclose(output);
}

void create_distance_map(struct image_data image, struct image_data template, struct image_data window, struct image_data dist)
{
    dist.height = (image.height - template.height);
    dist.width = (image.width - template.width);

    // recorremos la imagen
    for (int i = 0; i < (image.width - template.width); i++)
    {
        for (int j = 0; j < (image.height - template.height); j++)
        {
            // armamos la ventana con el mismo tamaño del template
            for (int n = i; n < (template.width + i); n++)
            {
                for (int m = j; m < (template.height + j); m++)
                {
                    // creamos una ventana con los elementos de I
                    window.array[n][m] = image.array[n][m];
                }
            }
            // calculamos la distancia entre los pixeles de la ventana con los del template
            compute_distance(template, window);
            dist.array[i][j] = distance;
        }
    }
}

void compute_distance(struct image_data template, struct image_data window)
{
    int sum;
    for (int i = 0; i < template.width; i++)
    {
        for (int j = 0; j < template.height; j++)
        {
            sum += (template.array[i][j] - window.array[i][j]) * (template.array[i][j] - window.array[i][j]);
        }
    }
    int norm = (255 * 255 * template.height * template.height) / 255;

    distance = sum / norm;
}