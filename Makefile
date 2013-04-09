# Makefile: CSE391 HW3 Problem 1
# Luby's maximal independent set algorithm

nbody: msort.C
			g++ msort.C -fopenmp -o msort

run:
	@ export OMP_NUM_THREADS=2
	@./msort 

run2:
	@ export OMP_NUM_THREADS=2
	@./msort
