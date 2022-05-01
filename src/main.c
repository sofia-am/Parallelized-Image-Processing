#include "../inc/file_processing.h"

int main(){
    /*
    if(argc < 2){
        printf("Ingrese el nombre de las imagenes a procesar\n");
    }
    */
    FILE *template_output;
    FILE *image_output;
    image_data image;
    image_data template;
    image_data window;

    // aloco memoria para la estructura
    window.array = malloc((unsigned long)template.width*sizeof(int*));
    for(int i = 0 ; i < template.width ; i++)
        window.array[i] = malloc((unsigned long)template.height*sizeof(int));

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

    char *image_src = "../img/DSC_2337_baw.pgm";
    char *template_src = "../img/test.pgm";

    load_image_to_array(image_src, image_output, image);
    load_image_to_array(template_src, template_output, template);
}