#include "../inc/file_processing.h"

int main(int argc, const char *argv[]){
    
    if(argc < 2){
        printf("Uso: %s <nombre_imagen>.pgm <nombre_template>.pgm\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
/* 
    printf("arg1: %s\n", argv[1]);
    printf("arg2: %s\n", argv[2]);
   */  
    image_data image, template, window, dist;

    FILE *template_output = fopen("template_output.txt", "a");
    if(!template_output){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    FILE *image_output = fopen("image_output.txt", "a");
    if(!image_output){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    FILE *archivo = fopen("distancia.pgm", "a");
    if(!archivo){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char *image_src = calloc(40, sizeof(argv[1]));
    sprintf(image_src, "../img/%s", argv[1]);
    char *template_src = calloc(40, sizeof(argv[2]));
    sprintf(template_src, "../img/%s", argv[2]);

    load_image_to_array(image_src, image_output, &image);
    load_image_to_array(template_src, template_output, &template);

    printf("Imagen: Ancho x Alto: %hu x %hu\n", image.width, image.height);
    printf("Template: Ancho x Alto: %hu x %hu\n", template.width, template.height);

    // aloco memoria para la estructura
    window.height = template.height;
    window.width = template.width;
    window.array = malloc((size_t)template.width*sizeof(u_int16_t *));
    for(int i = 0 ; i < template.width ; i++)
        window.array[i] = malloc((size_t)template.height*sizeof(u_int16_t));

    dist.array = malloc((size_t)image.width*sizeof(u_int16_t *));
    for(int i = 0; i < image.width; i++){
        dist.array[i] = malloc((size_t)image.height*sizeof(u_int16_t));
    }
    //printf("Guardé memoria");
    create_distance_map(&image, &template, &window, &dist);

    rewind(archivo);
    fprintf(archivo, "P2\n");
    fprintf(archivo, "%d %d\n", dist.width, dist.height);
    for(int i = 0; i < dist.width; i++){
        for(int j = 0; j < dist.height; j++){
            fprintf(archivo, "%d ", dist.array[i][j]);
        }
        fprintf(archivo, "\n");
    }
/*     
    free(&image);
    free(&template);
    free(&dist);
    free(&window); */
}