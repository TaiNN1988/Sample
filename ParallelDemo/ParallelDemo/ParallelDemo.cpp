#include "Common.h"
#include "Cpu/AddVector.h"
#include "Cpu/MulMatrix.h"

void testingAddVector();
void testMuMatrix_5_5();
void testMulMatrix();
void testingParallel();

int main(int argc, char* argv[])
{
	//
	//testingAddVector();
	//testMuMatrix_5_5();
	testMulMatrix();
	//testingParallel();

	return 0;
}





void testingParallel()
{
#pragma omp parallel for default(none),schedule(static,4)
	for (int index = 0; index < 12; index++)
	{
		printf("idx = %d\n", index);
	}
}


void testingAddVector()
{
	int size = 100000000;
	int* in1 = (int*)malloc(size * sizeof(int));
	int* in2 = (int*)malloc(size * sizeof(int));
	int* out = (int*)malloc(size * sizeof(int));

	// Init
	for (int i = 0; i < size; i++)
	{
		in1[i] = 1;
		in2[i] = 2;
	}

	addVectorParallel(out, in1, in2, size);


	// Compare
	for (int i = 0; i < size; i++)
	{
		int ori = in1[i] + in2[i];
		if (out[i] != ori) {
			printf("Failed!");
			break;
		}
	}
	printf("PASSED!");

	free(in1);
	free(in2);
	free(out);
}


void testMulMatrix()
{
	int halfSize = 2048;
	int* in1 = (int*)malloc(halfSize * halfSize * sizeof(int));
	int* in2 = (int*)malloc(halfSize * halfSize * sizeof(int));
	int* out = (int*)malloc(halfSize * halfSize * sizeof(int));

	// Initial array
	srand(time(NULL));
	for (size_t i = 0; i < halfSize; i++)
	{
		for (size_t j = 0; j < halfSize; j++)
		{
			in1[j + i * halfSize] = rand() % 1000 + 1;
			in2[j + i * halfSize] = rand() % 1000 + 1;
			out[j + i * halfSize] = 0;
		}
	}

	auto start = chrono::steady_clock::now();
	printf("Start...\n");
	mulMatrixOnHost_oneThread(out, in1, in2, halfSize);
	//mulMatrixOnHost_multipleThread(out, in1, in2, halfSize);
	auto end = chrono::steady_clock::now();
	printf("End\n");

	auto diff = end - start;

	auto diff_miSec = chrono::duration_cast<chrono::milliseconds>(diff);
	cout << "ExecutedTime = " << diff_miSec.count() << endl;

	printf(" show 10x10\n");
	showMatrix(out, 10);
}

void testMuMatrix_5_5()
{
	int in1[5][5] = {
		{1, 1, 1, 1, 1},
		{2, 2, 2, 2, 2},
		{3, 3, 3, 3, 3},
		{4, 4, 4, 4, 4},
		{5, 5, 5, 5, 5}
	};

	int in2[5][5] = {
		{1, 2, 3, 5, 1},
		{2, 2, 3, 5, 2},
		{3, 2, 3, 5, 3},
		{4, 2, 3, 5, 4},
		{5, 2, 3, 5, 5}
	};
	int out[5][5];
	int outExpected[5][5] = {
		{15, 10, 15, 25, 15},
		{30, 20, 30, 50, 30},
		{45, 30, 45, 75, 45},
		{60, 40, 60, 100, 60},
		{75, 50, 75, 125, 75}
	};

	int halfSize = 5;
	mulMatrixOnHost_oneThread(out[0], in1[0], in2[0], halfSize);

	// Compare
	for (size_t i = 0; i < halfSize; i++)
	{
		for (size_t j = 0; j < halfSize; j++)
		{
			if (out[i][j] != outExpected[i][j])
			{
				printf("Failed!");
				break;
			}
		}

	}
	printf("PASSED!");
}