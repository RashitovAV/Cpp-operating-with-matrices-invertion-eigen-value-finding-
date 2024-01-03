//#include "matrix_operations.h"
#include <algorithm>
using namespace std;
void Matrix_multiplication(double* m1, double *m2, double* r, int m1_s, int m1_c, int m2_c)
{
    //Матрица 1, Матрица 2, Итоговая матрица, Кол-во строк матрицы 1, Кол-во столбцов матрицы 1 = Кол-во строк матрицы 2, Кол-во столбцов матрицы 2
    //m1_s X m1_c * m1_c X m2_c => m1_s X m2_c
    int i, j, l;
    for (i = 0; i < m1_s; i++)
    {
        for (j = 0; j < m2_c; j++)
        {
            r[i * m1_s + j] = 0;
            for (l = 0; l < m1_c; l++)
            {
                r[i * m1_s + j] += m1[i * m1_c + l] * m2[l*m1_c+j];
            }
        }
    }
}
void Line_swap(double* a, int n, int l1, int l2)
{
    //Матрица, Размер матрицы, Номер строки 1, Номер строки 2
    for (int i = 0; i < n; i++)
    {
            swap(a[l1 * n + i], a[l2 * n + i]);
    }
}

void Line_addition(double* a, int n, int l1,int l2, double k1, double k2)
{
    //Матрица, Размер матрицы, Номер первой строки, Номер второй строки,Коэффициент домножения первой строки, Коэффициент домножения второй строки
    for(int j = 0; j < n; j++)
    {
        a[l1*n + j] = k1*a[l1*n+j] + k2*a[l2*n + j];
    }
}

void Line_multiplication(double* a, int n, int i, double k)
{
    //Матрица, Размер матрицы, Номер строки, коэффициент домножения
    for (int l = 0; l < n; l++)
    {
        a[i*n + l] *= k;
    }
}



void Column_addition(double* a, int n, int c1, int c2, double k)
{
    //Матрица, Размер матрицы, Номер первого столбца, Номер второго столбца, коэффициент домножения 
    for(int j = 0; j < n; j++)
    {
        a[c1 + j*n] += k*a[c2 + j*n];
    }
}

void Column_multpiplication(double* a, int n, int c, double k)
{
    //Матрица, Размер матрицы, номер столбца, коэффициент домножения
    int l;
    for (l = 0; l < n; l++)
    {
        a[c + l*n] *= k;
    }
}

