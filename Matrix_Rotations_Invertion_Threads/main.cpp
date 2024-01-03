#include "matrix_creator.h"
#include "matrix_operations.h"
#include "invertion.h"
#include "print_matrix.h"
#include "residual_norm.h"
#include "synchronizer.h"
#include <sys/time.h>
#include <ctime>
#include <thread>
using namespace std;
//метод вращений поиска обратной матрицы
int main(int argc, char* argv[]) //argc - количество аргументов которые следуют в argv[], argv[] - массив аргументов командной строки, которые вводятся пользователем
{
    if (argc < 5)
    {
        cout << "Not enough arguments in function main" << endl;
        return -1;
    }
    double elapsed, residual=0;
    int max_threads = thread::hardware_concurrency();
    int n = atoi(argv[1]);
    int p = atoi(argv[2]);
    if (p > max_threads)
    {
        p = max_threads;
    }
    int r = atoi(argv[3]);
    int s = atoi(argv[4]);
    int err = 0;
    if (n < 0 || r < 0)
    {
        cout << "Invalid n or m" << endl;
        return -1;
    }
    if (s < 0 || s > 4)
    {
        cout << "Invalid argument s in function main" << endl;
        return -1;
    }
    if (s == 0 && !argv[5])
    {
        cout << "Not enough arguments in function main" << endl;
        return -1;
    }
    double* input_matrix = new double[n * n];
    double* joined_matrix = new double[n * n];
    double* temporary_vector = new double[2 * n * p];
    double* add_vector = new double[2*n];
    int * deg_vector = new int[p];
    double* thread_time = new double[p];
    for (int i = 0; i < p; i++) { deg_vector[i] = 1; };
    Task_info* given_data = new Task_info[p];
    if (!input_matrix || !joined_matrix || !temporary_vector ||  !given_data || !thread_time||!add_vector)
    {
        printf("not enough memory");
        if (input_matrix) { delete[] input_matrix; };
        if (joined_matrix) { delete[] joined_matrix; };
        if (temporary_vector) { delete[] temporary_vector; };
        if(add_vector){delete[] add_vector;};
        if (thread_time) { delete[] thread_time; };
        if (given_data) { delete[] given_data; };
        return -1;
    }
    pthread_t * threads;
    if (!(threads = new pthread_t[p]))
    {
        printf("not enough memory for creating threads");
        delete[] input_matrix;
        delete[] joined_matrix;
        delete[] temporary_vector;
        delete[] add_vector;
        delete[] thread_time;
        delete[] deg_vector;
        delete[] given_data;
        return -1;
    }
    for (int i = 0; i < p; i++)
    {
        threads[i] = i;
    }
    if (s == 0 && (err = File_extractor(input_matrix,argv[5], n)) != 0)
    {
        cout << "Error " << err << " in matrix_creator" << endl;
        delete[] input_matrix;
        delete[] joined_matrix;
        delete[] temporary_vector;
        delete[] add_vector;
        delete[] thread_time;
        delete[] given_data;
        delete[] deg_vector;
        delete[] threads;
        return -1;
    }
    if(s == 0)
    {
        File_extractor(input_matrix, argv[5], n);
    }
    else
    {
        Matrix_generator_from_formula(input_matrix, s ,n);
    }
    //заполняем структуры данными
    int current_situation;
    printf("matrix A before algorithm:\n");
    Print_matrix(input_matrix, n, r, r);
    for (int i = 0; i < p; i++)
    {
        given_data[i].n = n;
        given_data[i].A = input_matrix;
        given_data[i].X = joined_matrix;
        given_data[i].T = temporary_vector;
        given_data[i].p_number = i;
        given_data[i].p = p;
        given_data[i].add_vector = add_vector;
        given_data[i].deg_vector = deg_vector;
        given_data[i].thread_time = thread_time;
        current_situation = pthread_create(&threads[i], NULL, Invertion_threaded, &given_data[i]);
        if (current_situation!=0)
        {
            printf("cannot create thread %d\n", i);
            for (int k = 0; k < i; k++)
            {
                if (pthread_join(threads[k], nullptr))
                {
                    printf("cannot wait thread %d", k);
                    delete[] input_matrix;
                    delete[] joined_matrix;
                    delete[] temporary_vector;
                    delete[] deg_vector;
                    delete[] thread_time;
                    delete[] add_vector;
                    delete[] given_data;
                    delete[] threads;
                    return -1;
                }
            }
            if (input_matrix) { delete[] input_matrix; };
            if (joined_matrix) { delete[] joined_matrix; };
            if (temporary_vector) { delete[] temporary_vector; };
            if (add_vector) {delete[] add_vector;};
            if (deg_vector) { delete[] deg_vector; };
            if (thread_time) { delete[] thread_time; };
            if (given_data) { delete[] given_data; };
            if (threads) { delete[] threads; };
            return -1;
        }
    }
    for (int i = 0; i < p; i++)
    {
        if (pthread_join(threads[i], nullptr))
        {
            printf("cannot wait thread %d", i);
            delete[] input_matrix;
            delete[] joined_matrix;
            delete[] temporary_vector;
            delete[] add_vector;
            delete[] thread_time;
            delete[] deg_vector;
            delete[] given_data;
            delete[] threads;
            return -1;
        }
    }
    for (int j = 0; j < p; j++)
    {
        if (deg_vector[j] == 0)
        {
            printf("Det of matrix is zero\n");
            delete[] input_matrix;
            delete[] joined_matrix;
            delete[] temporary_vector;
            delete[] add_vector;
            delete[] thread_time;
            delete[] deg_vector;
            delete[] given_data;
            delete[] threads;
            return -1;
        }
    }
    printf("Joined matrix:\n");
    Print_matrix(joined_matrix, n, r, r);

    elapsed = thread_time[0];
    delete[] thread_time;
    delete[] temporary_vector;
    delete[] deg_vector;
    delete[] add_vector;
    delete[] given_data;
    delete[] threads;
    if (s == 0)
    {
        File_extractor(input_matrix, argv[5], n);
    }
    else
    {
        Matrix_generator_from_formula(input_matrix, s, n);
    }

    
    // переходим к задаче нахождения нормы невязки
    double* residual_vector = new double[p];
    Task_residual * given_data_res = new Task_residual[p];
    if (!residual_vector || !given_data_res)
    {
        printf("not enough memory");
        if (input_matrix) { delete[] input_matrix; };
        if (joined_matrix) { delete[] joined_matrix; };
        if (residual_vector){ delete[] residual_vector; };
        if (given_data_res) { delete[] given_data_res; };
        return -1;
    }
    pthread_t* threads_res;
    if (!(threads_res = new pthread_t[p]))
    {
        printf("not enough memory for creating threads for residual norm");
        delete[] input_matrix;
        delete[] joined_matrix;
        delete[] residual_vector;
        delete[] given_data_res;
        return -1;
    }
    for (int i = 0; i < p; i++)
    {
        given_data_res[i].n = n;
        given_data_res[i].A = input_matrix;
        given_data_res[i].X = joined_matrix;
        given_data_res[i].residual_vector = residual_vector;
        given_data_res[i].p_number = i;
        given_data_res[i].p = p;
        current_situation = pthread_create(&threads_res[i], NULL, Residual_norm_threaded, &given_data_res[i]);
        if (current_situation != 0)
        {
            printf("cannot create thread %d\n", i);
            for (int k = 0; k < i; k++)
            {
                if (pthread_join(threads_res[k], nullptr))
                {
                    printf("cannot wait thread %d", k);
                    delete[] input_matrix;
                    delete[] joined_matrix;
                    delete[] residual_vector;
                    delete[] given_data_res;
                    delete[] threads_res;
                    return -1;
                }
            }
            if (input_matrix) { delete[] input_matrix; };
            if (joined_matrix) { delete[] joined_matrix; };
            if (residual_vector) { delete[] residual_vector; };
            if (given_data_res) { delete[] given_data; };
            if (threads_res) { delete[] threads_res; };
            return -1;
        }
    }
    for (int i = 0; i < p; i++)
    {
        if (pthread_join(threads_res[i], nullptr))
        {
            printf("cannot wait thread %d", i);
            delete[] input_matrix;
            delete[] joined_matrix;
            delete[] residual_vector;
            delete[] given_data_res;
            delete[] threads_res;
            return -1;
        }
    }
    for (int k = 0; k < p; k++)
    {
        if (residual < residual_vector[k])
        {
            residual = residual_vector[k];
        }
    }
    printf("%s : residual = %e elapsed = %.2f s = %d n = %d m = %d p = %d\n", argv[0], residual, elapsed, s, n, r, p);
    if(input_matrix){delete[] input_matrix;};
    if(joined_matrix){delete[] joined_matrix;};
    if(residual_vector){delete[] residual_vector;};
    if(given_data_res){delete[] given_data_res;};
    if(threads_res){delete[] threads_res;};
    return 0;
}
