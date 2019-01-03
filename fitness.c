/*
Justin Rosner
rosnej1
400137229

Principles of Programming - 2S03
Assignment #4
*/

#include "a4.h"
#include <stdlib.h>
#include <math.h>

#define SQR(x) (x)*(x)

// Creating a function the computes the distances between images at A and B
double comp_distance(const PIXEL *A, const PIXEL *B, int image_size){
	double distance = 0;
	double dr, dg, db;

	//summing the distance between each pixel in the two images
	for (int i = 0; i < image_size; i++){
		dr = SQR(A[i].r - B[i].r);
		dg = SQR(A[i].g - B[i].g);
		db = SQR(A[i].b - B[i].b);
		distance += (dr + dg + db);
	}

	// taking the square root of the summation
	double final_distance = sqrt(distance);

	// returning the distance between the two photos
	return final_distance;
}

// Making a function that will calculate the fitness values of a population 
void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size){
	int image_size = individual->image.width * individual->image.height;

	for (int i = 0; i < population_size; i++){
		(individual + i)->fitness = comp_distance(image, (individual + i)->image.data, image_size);
	}
}

