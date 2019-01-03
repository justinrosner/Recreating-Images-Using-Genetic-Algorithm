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

// making a function that will randomly select pixels and randomly select their RGB values
void mutate(Individual *individual, double rate){

	int max = individual->image.max_color;
	int n = individual->image.width * individual->image.height; 
	int num_rand_pixels = (int)(rate / 100 * n);

	for (int i = 0; i < num_rand_pixels; i++){
		int rand_index = rand() % n; // generating the rand index

		// generating random numbers from 0-max_color
		int rand_r = rand() % (max + 1); 
		int rand_g = rand() % (max + 1); 
		int rand_b = rand() % (max + 1); 

		// assigning the random numbers
		individual->image.data[rand_index].r = rand_r; 
		individual->image.data[rand_index].g = rand_g; 
		individual->image.data[rand_index].b = rand_b; 
	}
}

// making a function that will mutate all of the individuals in the population
void mutate_population(Individual *individual, int population_size, double rate){
	int n = population_size / 4;

	// loop that mutates the population
	for (int i = n; i < population_size; i++){
		mutate(individual + i, rate); 
	}
}