omp-file=omp_A_time
pthreads-file=pthreads_A_time

#---------OMP---------
omp: compile-omp run-omp
compile-omp:
	gcc-6 -fopenmp $(omp-file).c -o $(omp-file)
run-omp:
	./$(omp-file)

#---------PTHREADS---------
pthreads: compile-pthreads run-pthreads
compile-pthreads:
	gcc-6 -fopenmp $(pthreads-file).c -o $(pthreads-file)
run-pthreads:
	./$(pthreads-file)
