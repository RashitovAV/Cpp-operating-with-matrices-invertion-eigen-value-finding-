#include "matrix_creator.hpp"
#include "matrix_operations.hpp"
#include "invertion.hpp"
#include "print_matrix.hpp"
#include "residual_norm.hpp"
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) //argc - количество аргументов которые следуют в argv[], argv[] - массив аргументов командной строки, которые вводятся пользователем
{
    if(argc < 4)
    {
        cout << "Not enough arguments in function main" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);
    int err = 0;
    if (n < 0 || m < 0)
    {
        cout<<"Invalid n or m"<<endl;
        return -1;
    }
    if(k < 0 || k > 5)
    {
        cout << "Invalid argument k in function main" << endl;
        return -1;
    }
    if(k == 0 && !argv[4])
    {
        cout << "Not enough arguments in function main" << endl;
        return -1;
    }

    double* input_matrix;
    input_matrix = (double*)malloc(n*n*sizeof(double));
    double* joined_matrix;
    joined_matrix = (double*)malloc(n*n*sizeof(double));
    double* temporary_matrix;
    temporary_matrix = (double*)malloc(n * n * sizeof(double));
    double* input_matrix_copied;
    input_matrix_copied = (double*)malloc(n * n * sizeof(double));
    double* temporary_vector;
    temporary_vector = (double*)malloc(2*n*sizeof(double));
    double time_1, time_2;
    if (k == 0 && (err = File_extractor(input_matrix,argv[4], n)) != 0)
    {
        cout << "Error " << err << " in matrix_creator" << endl;
        free(input_matrix);
        free(joined_matrix);
        free(temporary_vector);
        free(input_matrix_copied);
        free(temporary_matrix);
        return -1;
    }
    if(k == 0)
    {
        File_extractor(input_matrix, argv[4], n);
    }
        else
            {
                Matrix_generator_from_formula(input_matrix, k ,n);
            }
    cout << "matrix A before algorithm:" << endl;
    Print_matrix(input_matrix, n, m, m);
    cout << endl;
    time_1 = clock();
    err = Invertion(n, input_matrix, joined_matrix,input_matrix_copied, temporary_vector);
    if(err != 0)
    {
        cout <<"Error "<< err << " in matrix invertion" << endl;
        free(input_matrix);
        free(joined_matrix);
        free(temporary_vector);
        free(input_matrix_copied);
        free(temporary_matrix);
        return -1;
    }
    time_1 = clock() - time_1;
    cout << "A after algorithm:" << endl;
    Print_matrix(input_matrix, n, m, m);
    cout << endl;
    cout << "Inverted matrix A^(-1):" << endl;
    Print_matrix(joined_matrix, n, m, m);
    printf("Time taken to find inversed matrix: %10.3e ms", 1000 * time_1 / CLOCKS_PER_SEC);
    cout << endl;
    time_2 = clock();
    printf("||AA^(-1)-E|| = %10.3e\n", Residual_norm(input_matrix_copied, joined_matrix, temporary_matrix, n));
    time_2 = clock() - time_2;
    printf("Time taken to find residual norm: %10.3e ms",1000 * time_2/CLOCKS_PER_SEC);
    cout << endl;
    printf("Total time: %10.3e ms", 1000 * (time_1+time_2) / CLOCKS_PER_SEC);
    cout << endl;
    free(input_matrix);
    free(joined_matrix);
    free(temporary_matrix);
    free(input_matrix_copied);
    free(temporary_vector);
    return 0;
}
