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
#include <time.h>

// The compare function to use with the sorting of the fitness values
int compare (const void *a, const void *b){

	Individual *ia = (Individual *)a;
	Individual *ib = (Individual *)b;

	if (ia->fitness > ib->fitness)
		return 1;
	else if (ia->fitness < ib->fitness)
		return -1;
	else
		return 0;
}

// This function frees the memory at the current image
void free_image(PPM_IMAGE *p){
	// freeing the struct of PIXELS
	free(p->data);
	free(p);
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, 
						int population_size, double rate){

	srand(time(NULL));

	int width = image->width;
	int height = image->height;
	int max_color = image->max_color;
	
	//Generating a random population of population_size
	Individual *population = generate_population(population_size, width, height, max_color);

	// Computing the fitness of each individual
	comp_fitness_population(image->data, population , population_size);
	

	// Sorting the individuals into non-decreasing order of fitness
	// The first individual will have the best fitness
	// ie. will have the shortest distance between the original image 
	qsort(population, population_size, sizeof(Individual), compare);

	for (int j = 1; j < num_generations; j++){
		// doing a crossover on the population
		crossover(population, population_size);

		// mutating the individuals
		mutate_population(population, population_size, rate);

		// computing the fitness of each individual
		comp_fitness_population(image->data, population, population_size);

		// sorting the individuals in non-decreasing order of fitness value
		qsort(population, population_size, sizeof(Individual), compare);

		if (j % 100 == 0){
			char output[20];
			sprintf(output, "escher%d.ppm", j/100);
			write_ppm(output, &(population[0].image));
		}
		
	}

	// creating a new image and assigning it the data it needs
	PPM_IMAGE *new_image;
	new_image = malloc(sizeof(PPM_IMAGE));
	new_image->data = population->image.data;
	new_image->width = population->image.width;
	new_image->height = population->image.height;
	new_image->max_color = population->image.max_color;

	// for loop that frees all of the PIXEL structs in the population except for the first one
	for(int k = 1; k < population_size; k++){
		free((population + k)->image.data);
	}

	// free the entire population
	free(population);

	return new_image;
}


