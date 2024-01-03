#include "residual_norm.hpp"
#include <stdio.h>
double Residual_norm(double* A, double* A_, double* temp_matrix, int n)
{
    //Исходная матрица, Обратная матрица, Временная матрица, Размер матрицы
    double norm = 0, temp_max=0;
    Matrix_multiplication(A, A_, temp_matrix, n, n, n);
    for (int i = 0; i < n; i++)
    {
        temp_matrix[i * n + i] -= 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp_max += fabs(temp_matrix[i * n + j]);
        }
        if (temp_max > norm)
        {
            norm = temp_max;
        }
        temp_max = 0;
    }
    
    return norm;
}

