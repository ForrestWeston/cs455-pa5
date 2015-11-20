#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#define INCIRC(x,y) (y-.5)*(y-.5) + (x-.5)*(x-.5)

int main(int argc, char *argv[]) {
	uint64_t n = 0, inCirc = 0, i;
	double x, y, tStart;
	struct drand48_data drandBuf;
	if (argc != 3) { printf("2 args, <n> <numProcs>"); exit(1); }
	n = atol(argv[1]);
	omp_set_num_threads(atoi(argv[2]));
	tStart = omp_get_wtime();
#pragma omp parallel private(i, x, y, drandBuf) shared(n)
{
	srand48_r(omp_get_thread_num(), &drandBuf);

#pragma omp for reduction(+:inCirc)
	for (i = 0; i < n; ++i) {
		drand48_r(&drandBuf, &x);
		drand48_r(&drandBuf, &y);
		if (INCIRC(x,y) <= .25) inCirc++;
	}
}
	printf("Num Procs %d\nItterations %lu\nRuntime %lf\nEstimate PI %.25lf\n",atoi(argv[2]),n,omp_get_wtime()-tStart,4.0*inCirc/n);
	return 0;
}
