filename=parallel_omp.c
filename=parallel_pthreads2.c

omp: compile run

compile:
	@gcc-6 -fopenmp -pthread $(filename)

run:
	@./a.out
