#include "invertion.hpp"
int Invertion(int n, double* A, double* X, double* A_, double* T)
{
    //������ �������, �������� �������, �������, � ������� ����� �������� ��������(��� ������ ������ ����������� n*n);�������, � ������� ��������� ��������, ������ ������� 2n, � ������� �������� ������ ������ ������� � � ������ ������� T
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
    }// ������� ������� X ���������(��� ���� �������������� �������), � ������ ���������� ������� � � ������� �_
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
                    //����� �� �������� �� ������������ (i,i) ������� ��������� ��������� ��������, ����� ������ (������ ���� ����� ����� ����)
                    //���� �� ���������� - ������ �������� ���� ����� � ������� ��� ������� i, ������� ���������, � �������� ���
                }
            }
        }

        if(fabs(A[i * n + i]) < Matrix_eps)
        {
            //�� ���������� �������� ������ ����� ���������� �� ���� �� ���������, �� ����������, ������ ������� ���������;
            return -1;
        }
        
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[j * n + i] - 0) > Matrix_eps)// ���� ������� �������, �� ������ ������ ���� ����
            {
                cos_phi = A[i * n + i] /sqrt(A[i * n + i] * A[i * n + i] + A[j * n + i] * A[j * n + i]);
                sin_phi =  (-1) * A[j * n + i] / sqrt(A[i * n + i] * A[i * n + i] + A[j * n + i] * A[j * n + i]);
                printf("\n\nworking with i =%d  and j =%d and cos =%10.3e and sin=%10.3e \n\n", i, j, cos_phi, sin_phi);
                for (int l = 0; l < n; l++)
                {
                    T[l] = A[i * n + l]; //���������� i-�� ������ � ������ A � X
                }
                for (int l = n; l < 2 * n; l++)
                {
                    T[l] = X[i * n + l - n];
                }
                Line_addition(A, n, i, j, cos_phi, -sin_phi); //i-�� ������ ���������� ��� ����� ��������� �� ������� ��������
                Line_addition(X, n, i, j, cos_phi, -sin_phi);
                for (int l = 0; l < n; l++)
                {
                    A[j * n + l] = sin_phi * T[l] + cos_phi * A[j * n + l]; //j-�� ������ ���������� ��� ����� ��������� �� ������� ��������
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
    }// �� ������ ������ �� ����� ����������������� �������
    
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
    
    //������� �����������������, �������� ���������� �������� ����� ������
    
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
