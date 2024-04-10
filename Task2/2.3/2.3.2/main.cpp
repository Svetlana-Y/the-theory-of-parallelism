#include <iostream>
#include <omp.h>
#include <fstream>
#include <chrono>

#define SIZE 13000
#define e 0.000000001
#define t 0.0001
#define MAXOFTHREADS 80

double cpuSecond()
{
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return ((double)ts.tv_sec + (double)ts.tv_nsec * 1.e-9);
}

void initialization(double* A, double* b, double* x) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i != j) A[i * SIZE + j] = 1.0;
			else A[i * SIZE + j] = 2.0;
		}
		x[i] = 0.0;
		b[i] = SIZE + 1;
	}
}

void reloadArray(double* x) {
	std::fill_n(x, SIZE, 0);
}

double criteriaForTheMethodWithoutFor(double* A, double* b, double* x, int countOfThreads) {

	#pragma omp single 
	double commonSumNumerator = 0, commonSumDenominator = 0;

	#pragma omp for 
		for (int i = 0; i < SIZE; i++) {
			double sumNumerator = 0, sumDenominator = 0;
			for (int j = 0; j < SIZE; j++) {
				sumNumerator += A[i * SIZE + j] * x[j];
			}
			sumNumerator = (sumNumerator - b[i]) * (sumNumerator - b[i]);

	#pragma omp atomic
			commonSumNumerator += sumNumerator;
			commonSumDenominator += (b[i] * b[i]);
		}
		return commonSumNumerator / commonSumDenominator;
}

void methodWithoutFor(double* A, double* b, double* x, int countOfThreads) {

	double* newX = new double[SIZE] {};

	#pragma omp parallel 
	while (criteriaForTheMethodWithoutFor(A, b, x, countOfThreads) > e) {
		
		#pragma omp for 
			for (int i = 0; i < SIZE; i++) {
				double sum = 0;
				for (int j = 0; j < SIZE; j++) {
					sum += A[i * SIZE + j] * x[j];
				}
				newX[i] = t * (sum - b[i]);
			}
		#pragma omp for 
			for (int i = 0; i < SIZE; i++)
				x[i] -= newX[i];
	}

}



void iterativeAlgorithm(double* A, double* b, double* x) {

	double timeForFirstThread;
	double S;

	std::ofstream output;
	output.open("dataFile.txt");
	if (output.is_open()) {
		for (int countOfThreads = 0; countOfThreads < MAXOFTHREADS; countOfThreads++) {
			double time = cpuSecond();
			methodWithoutFor(A, b, x, countOfThreads + 1);
			time = cpuSecond() - time;
			if (countOfThreads == 0) {
				timeForFirstThread = time;
			}
			S = timeForFirstThread / time;
			output << (countOfThreads + 1) << "," << time << "," << S << std::endl;
			std::cout << (countOfThreads + 1) << "- good" << std::endl;
			reloadArray(x);
		}
	}
}

int main(int argc, char* argv[]) {
	double* A = new double[SIZE * SIZE];
	double* b = new double[SIZE];
	double* x = new double[SIZE];

	initialization(A, b, x);
	iterativeAlgorithm(A, b, x);

	return 0;
}
