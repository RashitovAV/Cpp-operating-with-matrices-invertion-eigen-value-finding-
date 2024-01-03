#ifndef SYNCHRONIZER_HPP_INCLUDED
#define SYNCHRONIZER_HPP_INCLUDED


void synchronize(int);
double get_full_time(void);
struct Task_info
{
    int n;
    double* A;
    double* X;
    double* T;
    int p_number;
    int p;
    int* deg_vector; //��� ��� ���� ����� ����������� ������������� �������. ���� 1, �� ������� ���������, ����� �������� �� ���������
    double* thread_time;
    double* add_vector;
};

struct Task_residual
{
    int n;
    double* A;
    double* X;
    double* residual_vector;
    int p_number;
    int p;
};

#endif
