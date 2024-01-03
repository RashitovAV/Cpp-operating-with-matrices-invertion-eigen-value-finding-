#include "residual_norm.h"
#include "synchronizer.h"
#include <stdio.h>
#include <pthread.h>
void Residual_norm(int n, double* A, double* A_, int p_number, double *residual_vector, int p)
{
    //считаем ||AA^-1 - E||
    double temp_max = 0, temp_value=0, temp_element=0;
    int i, j, k;
    int first_row, last_row;
    first_row = n * p_number;
    first_row /= p;
    last_row = n * (p_number + 1);
    last_row = last_row / p - 1;
    for (i = first_row; i <= last_row; i++)
    {
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                temp_element += A[i * n + k] * A_[k * n + j];
            }
            if (j != i)
            {
                temp_value += fabs(temp_element);
                temp_element = 0;
            }
            else
            {
                temp_value += fabs(temp_element - 1);
                temp_element = 0;
            }
        }
        if (temp_value > temp_max)
        {
            temp_max = temp_value;
        }
        temp_value = 0;
    }
    residual_vector[p_number] = temp_max;
    synchronize(p);
}

void* Residual_norm_threaded(void* given_data_res)
{
    Task_residual* task_variables = (Task_residual*)given_data_res;
    Residual_norm(task_variables->n, task_variables->A, task_variables->X, task_variables->p_number, task_variables->residual_vector, task_variables->p);
    return NULL;
}

