#ifndef MATRIX_CREATOR_HPP_INCLUDED
#define MATRIX_CREATOR_HPP_INCLUDED
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std;

int File_extractor(double* a, char* file_name, int n);
double Formula_generator(int k, int n, int i, int j);
void Matrix_generator_from_formula(double* a, int k, int n);

#endif
