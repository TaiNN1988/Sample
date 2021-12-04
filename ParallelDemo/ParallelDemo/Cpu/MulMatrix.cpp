#include <omp.h>
#include "../Common.h"
#include "MulMatrix.h"

// out = A*B
void mulMatrixOnHost_oneThread(int* outMatrix, int* inMatrixA, int* inMatrixB, int halfSize)
{
	for (int i = 0; i < halfSize; i++)
	{
		for (int j = 0; j < halfSize; j++)
		{
			int sum = 0.0f;

			for (int k = 0; k < halfSize; k++)
			{
				sum = sum + inMatrixA[k + i * halfSize] * inMatrixB[j + k * halfSize];
			}
			outMatrix[j + i * halfSize] = sum;
		}
	}
}


// out = A*B
void mulMatrixOnHost_multipleThread(int* outMatrix, int* inMatrixA, int* inMatrixB, int halfSize)
{
#pragma omp parallel
	for (int i = 0; i < halfSize; i++)
	{
		if (i == 0)
		{
			printf("Threads: %d\n", omp_get_num_threads());
		}
		for (int j = 0; j < halfSize; j++)
		{
			int sum = 0.0f;

			for (int k = 0; k < halfSize; k++)
			{
				sum = sum + inMatrixA[k + i * halfSize] * inMatrixB[j + k * halfSize];
			}
			outMatrix[j + i * halfSize] = sum;
		}
	}

}
