#ifndef SOLUTION_HPP_INCLUDED
#define SOLUTION_HPP_INCLUDED
#include "synchronizer.h"
#include "matrix_operations.h"
#include <iostream>
#include <cmath>
using namespace std;
double Norm_of_matrix(int, double*);
void Zeros_are_zeros(int, double*, double*, double);
void Matrix_rotation(int, double*, double*, double*, int, int, int, int ,int, double *);
void Matrix_modification(int, double*, double*, double*, int, int, int, double, double*);
int Upper_triangle(int, double*, double*, double*, int, int, double,double*);
void Gauss(int, double*, double*, int*, int, int, double);
void *Invertion_threaded(void*);
#endif
