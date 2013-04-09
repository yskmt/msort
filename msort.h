#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>


// merge two sorted arrays
template <class T>
void merge(T* left, T* right,
		   const int n_left, const int n_right,
		   T* result,
		   T* tmp );

// mergesort with OpenMP parallelism
template <class T>
void mergesort(T* vec, const int threads, const int n,  T* tmp );

