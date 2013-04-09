#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

// merge two sorted arrays
void merge(int* left, int* right,
		   const int n_left, const int n_right,
		   int* result,
		   int* tmp )
{
	unsigned int it = 0;
    unsigned int left_it = 0, right_it = 0;
	// cout<<"n_left "<<n_left<<" n_right "<<n_right<<endl;
	
    while(left_it < n_left && right_it < n_right ) {
		it = left_it+right_it;
		// cout<<it<<endl;
		if(left[left_it] < right[right_it]) {
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
void mergesort(int* vec, int threads, int n,  int* tmp )
{
    // Termination condition: List is completely sorted if it
    // only contains a single element.
    if(n == 1){
		return;
	}

    // Determine the location of the middle element in the vector
	int* left = vec; // left array pointer
	int n_left = n/2; // number of elements in left array
	int* tmp_left = tmp; // left tmp array pointer
	
	int* right = left+n/2; // right array pointer
	int n_right = n-n/2; // number of elements in right array
	int* tmp_right = tmp+n/2; // right tmp array pointer
	
    // Perform a merge sort on the two smaller vectors
    if (threads > 1) {
		
		#pragma omp parallel sections
		{
			#pragma omp section
			{
				mergesort(left, threads/2, n_left, tmp_left);
			}
			#pragma omp section
			{
				mergesort(right, threads - threads/2, n_right, tmp_right);
			}
		}
	}
    else {
		mergesort(left, 1, n_left, tmp_left);
		mergesort(right, 1, n_right, tmp_right);
	}

    merge(left, right, n_left, n_right, left, tmp );

	return;
}

// int main()
// {
// 	// thread nesting enabled
// 	omp_set_nested(1);
		
// 	const int n = 10000;
// 	int v[n];
// 	int tmp[n];
	
// 	for (int i=0; i<n; ++i)
// 		v[i] = rand() % (n*5);

// 	// for (int i=0; i<n; ++i)
// 	// 	cout << v[i] << "\n";
	
// 	double start=omp_get_wtime();
// 	mergesort(v, 1, n, tmp);
// 	double end=omp_get_wtime();
// 	cout<<end-start<<endl;
	
// 	start=omp_get_wtime();
// 	mergesort(v, 2, n, tmp);
// 	end=omp_get_wtime();
// 	cout<<end-start<<endl;

// 	start=omp_get_wtime();
// 	mergesort(v, 4, n, tmp);
// 	end=omp_get_wtime();
// 	cout<<end-start<<endl;

// 	start=omp_get_wtime();
// 	mergesort(v, 8, n, tmp);
// 	end=omp_get_wtime();
// 	cout<<end-start<<endl;

// 	start=omp_get_wtime();
// 	mergesort(v, 16, n, tmp);
// 	end=omp_get_wtime();
// 	cout<<end-start<<endl;
  
// 	for (int i=0; i<n; ++i)
// 		cout << i<<" "<<v[i] << "\n";

// 	return 0;
// }
