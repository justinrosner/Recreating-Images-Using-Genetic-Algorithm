/*
Justin Rosner
rosnej1
400137229

Principles of Programming - 2S03
Assignment #4
*/

#include "a4.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Making a function to read the PPM image
PPM_IMAGE *read_ppm(const char *file_name){


    // Check and make sure that we do not have to check for comments, or if the file opened properly
    // Also ask about the specifier for unsigned chars


    PPM_IMAGE *initial_image = malloc(sizeof(PPM_IMAGE)); // Pointer to image struct
    FILE *open_file; // Pointer to the file that we have to read from

    open_file = fopen(file_name, "r");
    char temp_check[10];

    // Checking to make sure that the ppm file is of the right format
    fscanf(open_file, "%s", temp_check);
    if (strcmp(temp_check, "P3") != 0){
        printf("The file is not of the right format\n");
        exit(0);
    }
    
    // Getting the values for the height, width and max colour
    fscanf(open_file, "%d %d", &initial_image->width, &initial_image->height);
    fscanf(open_file, "%d", &initial_image->max_color);

    // Assigning the values of the pixels to data
    PIXEL *RGB_matrix; // Pointer to an array of the PIXEL structs
    int matrix_length = initial_image->height * initial_image->width;
    RGB_matrix = malloc(matrix_length * sizeof(PIXEL)); 
    for (int i = 0; i < matrix_length; i++){
        fscanf(open_file, "%hhu %hhu %hhu", &RGB_matrix[i].r, &RGB_matrix[i].g, &RGB_matrix[i].b);
    }
    
    initial_image->data = RGB_matrix;

    fclose(open_file); // Closing the file as we are now done reading
   
    // returns a pointer to a PPM_IMAGE structure
    return initial_image;
}

// Function that writes tto a ppm file
void write_ppm(const char *file_name, const PPM_IMAGE *image){

    FILE *open_file;
    open_file = fopen(file_name, "w");

    fprintf(open_file, "%s\n", "P3");
    fprintf(open_file, "%d %d\n", image->width, image->height);
    fprintf(open_file, "%d\n", image->max_color); 

    int temp_height = image->height;
    int temp_width = image->width;
    for (int i = 0; i < temp_height; i++){
        for (int j = 0; j < temp_width; j++){
            fprintf(open_file, "%hhu %hhu %hhu ", image->data[i * temp_width + j].r, 
                    image->data[i * temp_width + j].g, image->data[i * temp_width + j].b); 
        }
        fprintf(open_file, "%s", "\n" ); // print newline
    }

    fclose(open_file); // Closing the file as we are now done writing
}

