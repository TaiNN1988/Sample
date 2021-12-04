#include <omp.h>
#include "../Common.h"

void addVector(int* out, int* in1, int* in2, int size)
{
	for (int i = 0; i < size; i++)
	{
		out[i] = in1[i] + in2[i];
	}
}

void addVectorParallel(int* out, int* in1, int* in2, int size)
{

#pragma omp parallel for shared(out, in1, in2)
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			printf("Threads: %d\n", omp_get_num_threads());
		}

		out[i] = in1[i] + in2[i];
	}
}