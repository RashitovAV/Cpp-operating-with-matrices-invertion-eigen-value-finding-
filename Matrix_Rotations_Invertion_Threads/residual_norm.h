#ifndef RESIDUAL_NORM_HPP_INCLUDED
#define RESIDUAL_NORM_HPP_INCLUDED
#include "synchronizer.h"
#include "matrix_operations.h"
#include <iostream>
#include <cmath>
void Residual_norm(int, double*, double*, int,double *, int);
void* Residual_norm_threaded(void*);
#endif
