#include "msort.h"


// int compar(const int left, const int right)
// {
// 	return (left)<(right);

// }

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
// 	mergesort<int>(v, 1, n, tmp, compar);
// 	double end=omp_get_wtime();
// 	cout<<end-start<<endl;
	
// 	// start=omp_get_wtime();
// 	// mergesort(v, 2, n, tmp);
// 	// end=omp_get_wtime();
// 	// cout<<end-start<<endl;

// 	// start=omp_get_wtime();
// 	// mergesort(v, 4, n, tmp);
// 	// end=omp_get_wtime();
// 	// cout<<end-start<<endl;

// 	// start=omp_get_wtime();
// 	// mergesort(v, 8, n, tmp);
// 	// end=omp_get_wtime();
// 	// cout<<end-start<<endl;

// 	// start=omp_get_wtime();
// 	// mergesort(v, 16, n, tmp);
// 	// end=omp_get_wtime();
// 	// cout<<end-start<<endl;
  
// 	for (int i=0; i<n; ++i)
// 		cout << i<<" "<<v[i] << "\n";

// 	return 0;
// }
