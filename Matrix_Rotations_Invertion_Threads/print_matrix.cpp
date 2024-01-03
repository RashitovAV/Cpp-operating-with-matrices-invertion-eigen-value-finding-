#include "print_matrix.h"
#include <stdio.h>
#include <algorithm>
void Print_matrix(double* A, int n, int l, int m)
//матрица, размер матрицы, количество строк, количество столбцов
{
    for(int i = 0; i < l; i++)
    {
        if(i >= min(l, n)) break;
        for(int j = 0; j < m; j++)
        {
            if(j >= min(m, n)) break;
            printf("%10.3e ", A[i * n + j]);
        }
        printf("\n");
    }
}

