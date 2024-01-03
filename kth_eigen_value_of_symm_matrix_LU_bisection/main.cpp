#include "matrix_creator.hpp"
#include "solution.hpp"
#include "print_matrix.hpp"
#include <ctime>
#include <algorithm>
//Метод бисекции нахождения k-го по величине собственного значения симметричной матрицы с приведением ее 
//к трехдиагональному виду методом отражений и вычислением
//числа перемен знака в последовательности главных миноров с помощью LU - разложения
using namespace std;
//ввод: размер матрицы, размер вывода матрицы, точность, задание матрицы, порядок собственного значения, возможно имя файла
int main(int argc, char* argv[]) //argc - количество аргументов которые следуют в argv[], argv[] - массив аргументов командной строки, которые вводятся пользователем
{
    if (argc < 6)
    {
        printf("Not enough arguments in function main");
        return -1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    double Eps_input = atof(argv[3]);
    int k = atoi(argv[4]);
    int k_ = atoi(argv[5]);
    if (n < 0)
    {
        printf("Invalid n from input\n");
        return -1;
    }
    if (m < 0)
    {
        printf("Invalid m from input\n");
        return -1;
    }
    if (k < 0 || k > 4)
    {
        printf("Invalid argument k in function main\n");
        return -1;
    }
    if (k_ <= 0 || k_>n)
    {
        printf("Invalid question for number of eigen value\n");
        return -1;
    }
    if (k == 0 && !argv[6])
    {
        printf("Not enough arguments in function main\n");
        return -1;
    }
    double* input_matrix = new double [n*n];
    double* temporary_vector = new double[n];
    double* Vector_x = new double[n];
    double* Vector_y = new double[n];
    double* Vector_z = new double[n];
    double time_1;
    double result = 0;
    int err;
    if (k == 0 && (err = File_extractor(input_matrix,argv[6], n)) != 0)
    {
        cout << "Error " << err << " in matrix_creator" << endl;
        delete [] input_matrix;
        delete [] temporary_vector;
        delete [] Vector_x;
        delete [] Vector_y;
        delete [] Vector_z;
        return -1;
    }
    if(k == 0)
    {
        File_extractor(input_matrix, argv[6], n);
    }
        else
            {
                Matrix_generator_from_formula(input_matrix, k ,n);
            }
    printf("matrix A:\n");
    Print_matrix(input_matrix, n, m, m);
    printf("\n");

    
    //проверка матрицы на симметричность:
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (fabs(input_matrix[i * n + j] - input_matrix[j * n + i]) > Eps_input)
			{
				printf("Matrix is not symmetric\n");
                delete [] input_matrix;
                delete [] temporary_vector;
                delete [] Vector_x;
                delete [] Vector_y;
                delete [] Vector_z;
				return -1;
			}
		}
	}
	time_1 = clock();
    err = Solution(n, input_matrix, Vector_x, Vector_y, Vector_z, Eps_input, k_, &result);
    if(err < 0)
    {
        delete [] input_matrix;
        delete [] temporary_vector;
        delete [] Vector_x;
        delete [] Vector_y;
        delete [] Vector_z;
        return -1;
    }
    time_1 = clock() - time_1;

    printf("%d'st eigen value is %10.3e \n",k_, result);
    printf("Time taken to find  %i'st eigen value: %10.3e ms\n",k_ ,1000* time_1 / CLOCKS_PER_SEC);
    delete [] input_matrix;
    delete [] temporary_vector;
    delete [] Vector_x;
    delete [] Vector_y;
    delete [] Vector_z;
    return 0;
}
