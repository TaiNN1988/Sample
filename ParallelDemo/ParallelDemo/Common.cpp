#include "Common.h"

void showMatrix(int* matrix, int halfSize)
{
	for (size_t i = 0; i < halfSize; i++)
	{
		for (size_t j = 0; j < halfSize; j++)
		{
			printf("%d ", matrix[j + i * halfSize]);
		}
		printf("\n");
	}
}