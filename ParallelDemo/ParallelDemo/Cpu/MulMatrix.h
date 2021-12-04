#pragma once
void mulMatrixOnHost_oneThread(int* outMatrix, int* inMatrixA, int* inMatrixB, int halfSize);
void addVectorParallel(int* out, int* in1, int* in2, int size);