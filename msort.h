#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

// int(*compar)(const T *, const T *)
// 1 for left<right
// 0 for else

// merge two sorted arrays
template <class T>
void merge(T* left, T* right,
		   const int n_left, const int n_right,
		   T* result,
		   T* tmp,
		   int(*compar)(const T, const T)
		   );

// mergesort with OpenMP parallelism
template <class T>
void mergesort(T* vec, const int threads, const int n,  T* tmp,
			   int(*compar)(const T, const T)
			   );


// merge two sorted arrays
template <class T>
void merge(T* left, T* right,
		   const int n_left, const int n_right,
		   T* result,
		   T* tmp,
		   int(*compar)(const T, const T)
		   )
{
	unsigned int it = 0;
    unsigned int left_it = 0, right_it = 0;
	// cout<<"n_left "<<n_left<<" n_right "<<n_right<<endl;
	
    while(left_it < n_left && right_it < n_right ) {
		it = left_it+right_it;
		// cout<<it<<endl;
		if(compar(left[left_it], right[right_it])) {
			tmp[it] = left[left_it];
			left_it++;
		}
		else{
			tmp[it] = right[right_it];
			right_it++;
		}
	}

    // Push the remaining data from both vectors onto the tmp
    while(left_it < n_left) {
		it = left_it+right_it;
        tmp[it] = left[left_it];
        left_it++;
    }

    while(right_it < n_right) {
		it = left_it+right_it;
        tmp[it] = right[right_it];
        right_it++;
    }

	// Finally put everyhing in result array
	for(int i=0; i<(n_right+n_left); i++)
		result[i] = tmp[i];

}

// mergesort with OpenMP parallelism
template <class T>
void mergesort(T* vec, const int threads, const int n,  T* tmp,
			   int(*compar)(const T, const T)
			   )
{
    // Termination condition: List is completely sorted if it
    // only contains a single element.
    if(n == 1){
		return;
	}

    // Determine the location of the middle element in the vector
	T* left = vec; // left array pointer
	int n_left = n/2; // number of elements in left array
	T* tmp_left = tmp; // left tmp array pointer
	
	T* right = left+n/2; // right array pointer
	int n_right = n-n/2; // number of elements in right array
	T* tmp_right = tmp+n/2; // right tmp array pointer
	
    // Perform a merge sort on the two smaller vectors
    if (threads > 1) {
		
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(left, threads/2, n_left, tmp_left, compar);
			}
			#pragma omp section
			{
				mergesort(right, threads - threads/2, n_right, tmp_right, compar);
			}
		}
	}
    else {
		mergesort(left, 1, n_left, tmp_left, compar);
		mergesort(right, 1, n_right, tmp_right, compar);
	}

    merge(left, right, n_left, n_right, left, tmp, compar );

	return;
}
