#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>


// merge two sorted arrays
void merge(int* left, int* right,
		   const int n_left, const int n_right,
		   int* result,
		   int* tmp );

// mergesort with OpenMP parallelism
void mergesort(int* vec, int threads, int n,  int* tmp );

