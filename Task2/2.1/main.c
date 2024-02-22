#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

#define count_of_threads 40

void matrix_vector_product(double* a, double* b, double* c, int m, int n)
{
	for (int i = 0; i < m; i++) {
		c[i] = 0.0;
		for (int j = 0; j < n; j++)
			c[i] += a[i * n + j] * b[j];

	}
}

double run_serial(int M, int N)
{
	double* a, * b, * c;
	a = malloc(sizeof(*a) * M * N);
	b = malloc(sizeof(*b) * N);
	c = malloc(sizeof(*c) * M);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			a[i * N + j] = i + j;

	}
	for (int j = 0; j < N; j++)
		b[j] = j;

	double t = omp_get_wtime();
	matrix_vector_product(a, b, c, M, N);
	t = omp_get_wtime() - t;

	printf("Elapsed time (serial): %.6f sec.\n", t);
	free(a);
	free(b);
	free(c);

	return t;
}


void matrix_vector_product_omp(double* a, double* b, double* c, int M, int N)
{
#pragma omp parallel num_threads(count_of_threads)
	{
		int nthreads = omp_get_num_threads();
		int threadid = omp_get_thread_num();
		int items_per_thread = M / nthreads;
		int lb = threadid * items_per_thread;
		int ub = (threadid == nthreads - 1) ? (M - 1) : (lb + items_per_thread - 1);
		for (int i = lb; i <= ub; i++) {
			c[i] = 0.0;
			for (int j = 0; j < N; j++)
				c[i] += a[i * N + j] * b[j];

		}
	}
}




double run_parallel(int M, int N)
{
	double* a, *b, *c;
	// Allocate memory for 2-d array a[m, n]
	a = malloc(sizeof(*a) * M * N);
	b = malloc(sizeof(*b) * N);
	c = malloc(sizeof(*c) * M);

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++)
			a[i * N + j] = i + j;

	}
	for (int j = 0; j < M; j++)
		b[j] = j;

	double t = omp_get_wtime();
	matrix_vector_product_omp(a, b, c, M, N);
	t = omp_get_wtime() - t;
	printf("Elapsed time (parallel): %.6f sec.\n", t);

	free(a);
	free(b);
	free(c);

	return t;
}


int main(int argc, char** argv)
{
	size_t M = 1, N = 1;

	if (argc > 1)
		M = atoi(argv[1]);
	if (argc > 2)
		N = atoi(argv[2]);

	printf("Matrix-vector product (c[m] = a[m, n] * b[n]; m = %ld, n = %ld)\n", M, N);
	printf("Memory used: %"  PRIu64 " MiB\n", ((M * N + M + N) * sizeof(double)) >> 20);

	double tserial = run_serial(M, N);
	double tparallel = run_parallel(M, N);

	printf("Speedup: %.2f\n", tserial / tparallel);
	return 0;

}