#include "invertion.hpp"
int Invertion(int n, double* A, double* X, double* A_, double* T)
{
    //Размер матрицы, Исходная матрица, Матрица, в которую будет помещена обратная(это просто вектор размерности n*n);Матрица, в которую скопируем исходную, вектор размера 2n, в который временно класть строку матрицы А и строку матрицы T
    double cos_phi, sin_phi, A_max = 0, Matrix_eps=0, temp_max = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                X[i * n + j] = 1;
            }
            else
            {
                X[i * n + j] = 0;
            }
            A_[i * n + j] = A[i * n + j];
            if (fabs(A[i * n + j]) > A_max)
            {
                A_max = A[i * n + j];
            }
        }
    }// сделали матрицу X единичной(она есть присоединенная матрица), и заодно переписали матрицу А в матрицу А_
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp_max += fabs(A[i * n + j]);
        }
        if (temp_max > Matrix_eps)
        {
            Matrix_eps = temp_max;
        }
        temp_max = 0;
    }
    if (fabs(Matrix_eps -0)> 0)
    {
        Matrix_eps *= 1e-16;
    }
    else
    {
        return -1;
    }
    for(int i = 0; i < n; i++)
    {
        if(fabs(A[i * n + i] - 0) < Matrix_eps)
        {
            for(int p = i + 1; p < n; p++)
            {
                if(fabs(A[p * n + i] - 0) > Matrix_eps)
                {
                    Line_swap(A, n, i, p);
                    Line_swap(X, n, i, p);
                    break;
                    //здесь мы пытаемся на диагональный (i,i) элемент поставить ненулевое значение, меняя строки (причем ищем среди строк ниже)
                    //если не получается - значит получаем угол нулей в столбце под номером i, матрица вырождена, и обратной нет
                }
            }
        }

        if(fabs(A[i * n + i]) < Matrix_eps)
        {
            //мы попытались поменять строки чтобы избавиться от нуля на диагонали, не получилось, значит матрица вырождена;
            return -1;
        }
        
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[j * n + i] - 0) > Matrix_eps)// если элемент нулевой, то смысла гонять цикл нету
            {
                cos_phi = A[i * n + i] /sqrt(A[i * n + i] * A[i * n + i] + A[j * n + i] * A[j * n + i]);
                sin_phi =  (-1) * A[j * n + i] / sqrt(A[i * n + i] * A[i * n + i] + A[j * n + i] * A[j * n + i]);
                printf("\n\nworking with i =%d  and j =%d and cos =%10.3e and sin=%10.3e \n\n", i, j, cos_phi, sin_phi);
                for (int l = 0; l < n; l++)
                {
                    T[l] = A[i * n + l]; //запоминаем i-ые строки у матриц A и X
                }
                for (int l = n; l < 2 * n; l++)
                {
                    T[l] = X[i * n + l - n];
                }
                Line_addition(A, n, i, j, cos_phi, -sin_phi); //i-ая строка становится как после умножения на матрицу вращения
                Line_addition(X, n, i, j, cos_phi, -sin_phi);
                for (int l = 0; l < n; l++)
                {
                    A[j * n + l] = sin_phi * T[l] + cos_phi * A[j * n + l]; //j-ая строка становится как после умножения на матрицу вращения
                }
                for (int l = n; l < 2 * n; l++)
                {
                    X[j * n + l - n] = sin_phi * T[l] + cos_phi * X[j * n + l - n];
                } 
            }
            for (int t = 0; t < n; t++)
            {
                for (int s = 0; s < n; s++)
                {
                    //printf("\n\nWE ARE IN PM FUCTION\n\n");
                    printf("%10.3e ", A[t * n + s]);
                }
                printf("\n");
            }
        }
    }// на данный момент мы имеем верхнетреугольную матрицу
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fabs(A[i * n + j]-0) < Matrix_eps)
            {
                A[i * n + j] = 0;
            }
            if (fabs(X[i * n + j]-0) < Matrix_eps)
            {
                X[i * n + j] = 0;
            }
        }
    }
    
    //матрица верхнетреугольная, осталось зафигачить обратный метод гаусса
    
    for (int i =n-1; i>0;i--)
    {
        
        for (int j = 0; j<i;j++)
        {
                Line_addition(X, n, j, i, 1, (-1) * A[j * n + i] / A[i * n + i]);
                Line_addition(A, n, j, i, 1, (-1) * A[j * n + i] / A[i * n + i]);
        }
        for (int k = 0; k < n; k++)
        {
            X[i * n + k] /= A[i * n + i];
        }
        A[i * n + i] /= A[i * n + i];
    }
    for (int k = 0; k < n; k++)
    {
        X[k] /= A[0];
    }
    A[0] /= A[0];
    
    return 0;
}
