/*
Justin Rosner
rosnej1
400137229

Principles of Programming - 2S03
Assignment #4
*/

#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

// Creating a function that generates a random image
PIXEL *generate_random_image(int width, int height, int max_color){

	int matrix_length = width * height;
	PIXEL *random_image;
	random_image = malloc(matrix_length * sizeof(PIXEL));

	for (int i = 0; i < matrix_length; i++){
		random_image[i].r = rand() % (max_color + 1);
		random_image[i].g = rand() % (max_color + 1);
		random_image[i].b = rand() % (max_color + 1); 
	}

	// returning an array of random PIXELS
	return random_image;
}

// Creating a function that creates a population
Individual *generate_population(int population_size, int width, int height, int max_color){
	Individual *population;
	population = malloc(population_size * sizeof(Individual));

	for (int i = 0; i < population_size; i++){
		population[i].image.data = generate_random_image(width, height, max_color);
		population[i].image.width = width;
		population[i].image.height = height;
		population[i].image.max_color = max_color;
	}

	// returning an array of individuals
	return population;
}