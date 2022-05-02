#include "../inc/file_processing.h"

int main(){
    /*
    if(argc < 2){
        printf("Ingrese el nombre de las imagenes a procesar\n");
    }
    */
    FILE *template_output;
    FILE *image_output;
    struct image_data data, template_data;

    template_output = fopen("template_output.txt", "a");
    if(!template_output){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    image_output = fopen("image_output.txt", "a");
    if(!image_output){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }

    char *imagen = "../img/DSC_2337_baw.pgm";
    char *template = "../img/test.pgm";

    load_image_to_array(imagen, image_output, &data);
    load_image_to_array(template, template_output, &template_data);
    
    printf("Imagen: Ancho x Alto: %d x %d\n", data.width, data.height);
    printf("Template: Ancho x Alto: %d x %d\n", template_data.width, template_data.height);

}