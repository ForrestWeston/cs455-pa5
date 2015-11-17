#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <omp.h>

#define PRIME 1039
#define X1 .5
#define Y1 .5
#define R .5

#define PI 3.141592653589793238462643383279

int InCircle(double x, double y)
{
	double res = sqrt(((y-Y1)*(y-Y1)) + ((x-X1)*(x-X1)));
	if (res <= R) return 1;
	return 0;
}

int main(int argc, char *argv[])
{
	int p = 1;
	uint64_t n = 0;
	int i;
	uint64_t inCirc = 0;
	double x, y;
	double tStart, tEnd;
	struct drand48_data drandBuf;
	if (argc != 3) {
		printf("'Forrest's Pi Estimator' takes 2 args <n> <num threads>\n");
		exit(1);
	}

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	omp_set_num_threads(p);

	tStart = omp_get_wtime();

#pragma omp parallel private(i, x, y, drandBuf) shared(n)
{

	srand48_r(PRIME*omp_get_thread_num(), &drandBuf);

#pragma omp for reduction(+:inCirc)
	for (i = 0; i < n; i++) {
		drand48_r(&drandBuf, &x);
		drand48_r(&drandBuf, &y);
		if (InCircle(x,y)) inCirc++;
	}
}
	tEnd = omp_get_wtime();
	double estimate = 4.0*inCirc/n;
	printf("%d, %lu, %lf, %.25lf\n",p,n, tEnd-tStart, estimate);
	/*
	printf("Est. PI:\t %lf\n", 4.0*inCirc/n);
	printf("PI:\t\t 3.141592653589793238462643383279\n");
	printf("Time %lf\n", tEnd-tStart);
*/
	return 0;
}


