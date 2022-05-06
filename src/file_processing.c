#include "../inc/file_processing.h"

void load_image_to_array(char *image_to_open, FILE *output, image_data *data)
{
    // Variables
    FILE *imagen;
    char line[200];
    int x, y;
    // Abro la imagen
    //printf("Abriendo el archivo %s\n", image_to_open);
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
    //printf("Leyendo la información del header\n");
    rewind(imagen);
    int status = fscanf(imagen, "%[^\n]\n", line);
    status = fscanf(imagen, "%hu %hu\n", &data->width, &data->height);
    status = fscanf(imagen, "%[^\n]\n", line);
    if (status == -1)
    {
        perror("Error leer informacion");
        exit(EXIT_FAILURE);
    }

    data->array = malloc((size_t)data->width * sizeof(u_int16_t *));
    for (int i = 0; i < data->width; i++)
        data->array[i] = malloc((size_t)data->height * sizeof(u_int16_t));

    // Almaceno en un->array de 2 dimensiones
    printf("Procesando la imagen %s\n", image_to_open);
    x = 0;
    while (x < data->height)
    {
        y = 0;
        while (y < data->width)
        {
            status = fscanf(imagen, "%hu", &data->array[x][y]);
            if (status == -1)
            {
                perror("Error leer informacion");
                exit(EXIT_FAILURE);
            }
            fprintf(output, "%hu ", data->array[x][y]);
            y++;
        }
        fprintf(output, "\n");
        x++;
    }
    // Cerramos los files abiertos
    //printf("Alto x Ancho: %hu %hu\n", data->width, data->height);

    //printf("Cerrando el archivo %s\n", image_to_open);
    fclose(imagen);
    fclose(output);
}

void create_distance_map(image_data *image, image_data *template, image_data *window, image_data *dist)
{   
    unsigned int distance = 0;
    int aux = __INT_MAX__;
    u_int16_t max = 255;
    u_int16_t fila_t = 0;
    u_int16_t column_t = 0;
    int i, j, m, n;
    unsigned int norm = (unsigned int)(max * max * template->height * template->width) / max;
    dist->height = (u_int16_t)(image->height - template->height);
    dist->width = (u_int16_t)(image->width - template->width);
    //printf("Entré ");
    // recorremos la imagen
    #pragma omp parallel for private(i, j, m, n) num_threads(4);

    for ( i = 0; i < (image->height - template->height); i++)
    {
        for ( j = 0; j < (image->width - template->width); j++)
        {
            //aux = distance;
            distance = 0;
            // armamos la ventana con el mismo tamaño del template
            for ( n = 0; n < (template->height); n++)
            {
                for ( m = 0; m < (template->width); m++)
                {
                    // creamos una ventana con los elementos de I
                    window->array[n][m] = image->array[n+i][m+j];
                }
            }
            // calculamos la distancia entre los pixeles de la ventana con los del template
            distance = compute_distance(template, window);
            dist->array[i][j] = (u_int16_t)(distance/norm);
            if(distance <= aux){
                fila_t = (i + template->height/2);
                column_t = (j + template->width/2);
                aux = distance;
            }
        }
    }
    printf("Valor minimo: %d\n", (distance/norm));
    printf("Minimo [%d][%d]\n", column_t, fila_t);
}

unsigned int compute_distance(image_data *template, image_data *window)
{   
    //u_int16_t distance;
    unsigned int sum = 0;
    
/*     u_int16_t temp = 0;
    u_int16_t aux = 0;
    u_int16_t max = 255;
 */
    for (int i = 0; i < template->height; i++)
    {
        for (int j = 0; j < template->width; j++)
        {
            sum += (unsigned int)((template->array[i][j] - window->array[i][j]) * (template->array[i][j] - window->array[i][j]));
        }
    }
    return sum;
} 