#include "matrix_creator.hpp"

int File_extractor(double *a,char * file_name, int n)
{
    FILE* f;
    f = fopen(file_name, "r");
    if (!f)
    {
        cout << "File didn't open\n";
        return -1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(f, "%lf", a + i * n + j) != 1)
            {
                fclose(f);
                cout << "Not enough arguments in file or problems with elements in file\n"<<endl;
                return -2;
            }
        }
    }
    fclose(f);
    return 0;
}
double Formula_generator(int k, int n, int i, int j)
{
    int i1 = i + 1;
    int j1 = j + 1;
    switch (k)
    {
    case 1: 
        return n - max(i1, j1) + 1;
        break;
    case 2: 
        if (i1 == j1)
        {
            return 2;
        }
        else if (i1 - j1 == 1)
        {
            return -1;
        }
        else if (j1 - i1 == 1)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    case 3: 
        if (i1 == j1 && i1<n)
        {
            return 1;
        }
        else if (i1 == n)
        {
            return j1;
        }
        else if (j1 == n)
        {
            return i1;
        }
        else
        {
            return 0;
        }
    case 4: 
        return 1./ (i1 + j1 - 1);
    }
    return 0;
}
void Matrix_generator_from_formula(double* a, int k, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            a[i * n + j] = Formula_generator(k, n, i, j);
        }
    }
}
