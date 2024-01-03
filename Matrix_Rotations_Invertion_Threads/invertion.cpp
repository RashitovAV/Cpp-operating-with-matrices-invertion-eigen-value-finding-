#include "invertion.h"
#include "synchronizer.h"
#include <pthread.h>
double Norm_of_matrix(int n, double* A)
{
    int i, j;
    double temp_max = 0, temp_value=0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            temp_value += fabs(A[i * n + j]);
        }
        if (temp_value > temp_max)
        {
            temp_max = temp_value;
        }
        temp_value = 0;
    }
    if (fabs(temp_max - 0) > 0)
    {
        temp_max *= 1e-16;
    }
    else
    {
        return -1;
    }
    return temp_max;
}
void X_declaration(int n, double* X)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
            {
                X[i * n + j] = 1;
            }
            else
            {
                X[i * n + j] = 0;
            }
        }
    }// сделали матрицу X единичной(она есть присоединенная матрица)
}
void Zeros_are_zeros(int n, double* A, double* X, double Matrix_eps)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (fabs(A[i * n + j]) < Matrix_eps)
            {
                A[i * n + j] = 0;
            }
            if (fabs(X[i * n + j]) < Matrix_eps)
            {
                X[i * n + j] = 0;
            }
        }
    }
}
void Matrix_rotation(int n, double* A, double* X, double* T, int p_number, int i, int j, int first_row, int last_row,double * add_vector)
{
    double cos_phi = add_vector[j];
    double sin_phi = add_vector[n+j];
    for (int l = first_row; l <= last_row; l++)
    {
        T[p_number * n + l] = A[i * n + l]; //запоминаем i-ые строки у матриц A и X
    }

    for (int l = first_row; l <= last_row; l++)
    {
        T[p_number * n + (l + n)] = X[i * n + l];
    }
    for (int k = first_row; k <= last_row; k++)
    {
        A[i * n + k] = cos_phi * A[i * n + k] - sin_phi * A[j * n + k];
    }

    for (int k = first_row; k <= last_row; k++)
    {
        X[i * n + k] = cos_phi * X[i * n + k] - sin_phi * X[j * n + k];
    }
    for (int l = first_row; l <= last_row; l++)
    {
        A[j * n + l] = sin_phi * T[p_number * n + l] + cos_phi * A[j * n + l]; //j-ая строка становится как после умножения на матрицу вращения
    }
    for (int l = first_row; l <= last_row; l++)
    {
        X[j * n + l] = sin_phi * T[p_number * n + (l + n)] + cos_phi * X[j * n + l];
    }
}
void Matrix_modification(int n, double* A, double* X, double* T, int p_number, int p, int i, double Matrix_eps, double* add_vector)
{
    int first_row, last_row;
    first_row = n * p_number / p;
    last_row = n * (p_number + 1) / p - 1;
    double cos_phi = 0, sin_phi = 0;
    double temporary_element=A[i*n+i];
    synchronize(p);
    for (int j = i+1; j < n; j++)
    {
        if (p_number == 0)
        {
            if (fabs(A[j * n + i]) > Matrix_eps || fabs(A[i*n+i])>Matrix_eps)
            {
            cos_phi = temporary_element / sqrt(temporary_element * temporary_element + A[j * n + i] * A[j * n + i]);
            sin_phi = (-1) * A[j * n + i] / sqrt(temporary_element * temporary_element + A[j * n + i] * A[j * n + i]);
            temporary_element = sqrt(temporary_element * temporary_element + A[j * n + i] * A[j * n + i]);
            add_vector[j] = cos_phi;
            add_vector[n+j] = sin_phi;
            }
            else
            {
                cos_phi = 2; 
                sin_phi = 2;
                add_vector[j] = cos_phi;
                add_vector[n+j] = sin_phi;
            }
        }
    }
    synchronize(p);
    for (int j = i+1 ; j<n; j++)
    {
        if(!(add_vector[j]>1.5))
        {
            Matrix_rotation(n, A, X, T, p_number, i, j, first_row, last_row, add_vector);
        }
        for(int t = 0; t < n; t++)
    } 
    synchronize(p);
}
int Upper_triangle(int n, double* A, double* X, double* T,int p_number, int p, double Matrix_eps, double* add_vector)
{
    for (int i = 0; i < n; i++)
    {
        Matrix_modification(n, A, X, T, p_number, p, i, Matrix_eps, add_vector);
    }
    return 0;
}
int Gauss_step(int n, double* A, double* X, int p_number, int p, double Matrix_eps, int i)
{
    int first_row = n * p_number / p;
    int last_row = n * (p_number + 1) / p - 1;
    for (int j = first_row; j <= last_row; j++)
    {
        double counter = 0;
        for (int k = i + 1; k < n; k++)
        {
            counter += A[i * n + k] * X[k * n + j];
        }
        if (fabs(A[i * n + i]) > Matrix_eps)
        {
            X[i * n + j] = X[i * n + j] - counter;
            X[i * n + j] /= A[i * n + i];
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
void Gauss(int n, double *A, double*X,int * deg_vector, int p_number, int p, double Matrix_eps)
{
    for (int i = n - 1; i >= 0; i--)
    {
        synchronize(p);
        int result = Gauss_step(n, A, X,p_number, p, Matrix_eps, i);
        if (result != 0)
        {
            deg_vector[p_number] = 0;
            break;
        }
    }
    synchronize(p);
}
void* Invertion_threaded(void* given_data)
{
    Task_info* task_variables = (Task_info*)given_data;
    double matrix_eps;
    double elapsed_time = get_full_time();
    matrix_eps = Norm_of_matrix(task_variables->n, task_variables->A);//вычисление матричного эпсилона
    if (matrix_eps < -1./2)
    {
        task_variables->deg_vector[0] = 0;
        return 0;
    }
    X_declaration(task_variables->n, task_variables->X);//задание матрицы единичной
    int checker = Upper_triangle(task_variables->n, task_variables->A, task_variables->X, task_variables->T, task_variables->p_number, task_variables->p,  matrix_eps, task_variables->add_vector);
    if (checker != 0)
    {
        return 0;
    }
    Zeros_are_zeros(task_variables->n, task_variables->A, task_variables->X, matrix_eps);
    Gauss(task_variables->n, task_variables->A, task_variables->X,task_variables->deg_vector, task_variables->p_number, task_variables->p, matrix_eps);
    task_variables->thread_time[0] = get_full_time() - elapsed_time;
    return 0;
}
