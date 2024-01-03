#ifndef MATRIX_OPERATIONS_HPP_INCLUDED
#define MATRIX_OPERATIONS_HPP_INCLUDED

#include <stdlib.h>
#include <algorithm>
using namespace std;

void Matrix_multiplication(double* , double* , double* , int, int, int);

void Line_swap(double* , int, int, int);

void Line_addition(double* , int, int, int, double, double);

void Line_multiplication(double* , int, int, double);

void Column_addition (double* , int,int, int, double);

void Column_multpiplication(double* , int, int, double );

#endif 
