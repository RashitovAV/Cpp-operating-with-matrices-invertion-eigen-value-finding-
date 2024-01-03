#include "solution.hpp"
int Reflection_method(int n, double* A, double* Vector_x, double* Vector_y, double* Vector_z, double input_eps)
{
	int i, j, l;
	// норма подстолбца(подстроки), норма (подстолбец - normA*e_i) , просто переменная
	double norm_A = 0, norm_A_a = 0, temp_value = 0;
	for (i = 1; i < n - 1; i++)
	{
		for (j = i; j < n; j++)
		{
			norm_A += A[j * n + (i - 1)] * A[j * n + (i - 1)];
			if (j > i)
			{
				norm_A_a += A[j * n + (i - 1)] * A[j * n + (i - 1)];
			}
		}
		norm_A = sqrt(norm_A);
		norm_A_a += (A[i * n + (i - 1)] - norm_A) * (A[i * n + (i - 1)] - norm_A);
		if (fabs(norm_A_a) < input_eps)
		{
			//если это так, тогда отражать нет смысла: подстолбец уже нужного вида
			norm_A = 0;
			norm_A_a = 0;
			continue;
		}
		norm_A_a = sqrt(norm_A_a);
		//x = (a - ||a||*e_i)/||(a - ||a||*e_i)|| -вектор длины n-i, а первые i координат задаем равными нулю
		Vector_x[i] = (A[i * n + (i - 1)] - norm_A) / norm_A_a;
		for (j = i + 1; j < n; j++)
		{
			Vector_x[j] = A[j * n + (i - 1)] / norm_A_a;
		}
		for (j = 0; j < i; j++)
		{
			Vector_x[j] = 0;
		}
		norm_A = 0;
		norm_A_a = 0;
		//y = Ax, где A - подматрица
		for (j = 0; j < n; j++)
		{
			for (l = 0; l < n; l++)
			{
				temp_value += A[j * n + l] * Vector_x[l];
			}
			Vector_y[j] = temp_value;
			temp_value = 0;
		}
		for (j = 0; j < n; j++)
		{
			//считаем скалярное произведение х и у
			temp_value += Vector_x[j] * Vector_y[j];
		}
		//z  = 2y - 2(x,y)x
		for (j = 0; j < n; j++)
		{
			Vector_z[j] = 2 * Vector_y[j] - 2 * temp_value * Vector_x[j];
		}
		temp_value = 0;
		//теперь нам надо посчитать A - 2 zx^ - 2 xz^. Это и будет результирующая матрица 
		for (j = i-1; j < n; j++)
		{
			for (l = i-1; l < n; l++)
			{
				A[j * n + l] = A[j * n + l] - Vector_x[j] * Vector_z[l] - Vector_x[l] * Vector_z[j];
			}
		}
		
	}
	return 0;
}

int LU_decomp_Sign_change(int n, double* A, double* Vector_l, double* Vector_lambda, double* Vector_u,double input_eps, double lambda)
{
	int number_of_changes = 0;
    int sign_wehave;
	Vector_l[0] = A[0] - lambda;
	if (Vector_l[0]<0)
	{ 
		number_of_changes++;
        sign_wehave =-1;
	}
	else
    {
        sign_wehave = 1;
    }
	if (fabs(Vector_l[0]) < input_eps) 
	{
		Vector_l[0] = input_eps;
	}
	Vector_u[0] = A[1] / fabs(Vector_l[0]);
	Vector_lambda[0] = A[n];
	for (int i = 1; i < n - 1; i++) 
	{
		Vector_l[i] = A[n * i + i] - lambda - Vector_lambda[i - 1] * Vector_u[i - 1]*sign_wehave;
		if (Vector_l[i] < 0)
		{
			number_of_changes++;
            sign_wehave =-1;
		}
		else
        {
            sign_wehave = 1;
        }
		if (fabs(Vector_l[i]) < input_eps) 
		{
			Vector_l[i] = input_eps;
		}
		Vector_u[i] = A[n * i + (i + 1)] / fabs(Vector_l[i]);
		Vector_lambda[i] = A[n * (i + 1) + i];
	}
	Vector_l[n - 1] = A[n * (n - 1) + (n - 1)] - lambda - Vector_lambda[n - 2] * Vector_u[n - 2]*sign_wehave;
	if (Vector_l[n - 1] < 0)
	{
		number_of_changes++;
	}
	//printf("\nVector_l is %10.3e , %10.3e , %10.3e\n", Vector_l[0], Vector_l[1], Vector_l[2]);
	//теперь нужно посчитать количество перемен знака в последовательности главных миноров матрицы А
	//так как главный минор размера i матрицы A теперь равен l1*l2*...*li, нужно просто посчитать количество отрицательных li
	//это и будет количество смен знака в последовательности главных миноров матрицы А
	return number_of_changes;
}
int Bisection_method(int n, double* A, double* Vector_l, double* Vector_lambda, double* Vector_u, double norm_A_inf, double input_eps, int k, double *result)
{
	double a = -norm_A_inf, b = norm_A_inf, c;
	int r;
	//counter> log[(b-a)/input_eps]
	double counter = 2 * log2((b - a) / input_eps);
	while (b - a > input_eps && counter>=0)
	{
		//printf("\n b-a is %10.3e\n", b - a);
		c = (a + b) / 2;
		r = LU_decomp_Sign_change(n, A, Vector_l, Vector_lambda, Vector_u, input_eps, c);
		if (r < k)
		{
			a = c;
		}
		else
		{
			b = c;
		}
		counter-=1;
	}
	*result = (a + b) / 2;
	return 0;
}
int Solution(int n, double* A, double* Vector_x, double* Vector_y, double* Vector_z, double input_eps,int k, double *result)
{
	if (n == 1)
	{
		*result = A[0];
		return 0;
	}
	double norm_A_inf=0, temp_value = 0;
    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			temp_value += fabs(A[i * n + j]);
		}
		if (temp_value > norm_A_inf)
		{
			norm_A_inf = temp_value;
		}
		temp_value = 0;
	}
	if (!(norm_A_inf > 0))
	{
		//printf("All elements of matrix are zero, so are eigen values are zero, so answer is zero\n");
        result = 0;
        return 0;
	}
	/*
	if (Eps_input <= 2 * matrix_eps)
	{
		//предполагается, что эпс инпат больше чем матричный эпсилон, иначе мы "не почувствуем" собственного значения 
		//printf("accuracy is too small:(\n");
		//printf("2 * matrix eps is : %10.3e\n",  2 * matrix_eps);
		return -1;
	}
	*/
	Reflection_method(n, A, Vector_x, Vector_y, Vector_z, input_eps);
	/*
	printf("Matrix A after reflection method:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%10.3e ", A[i * n + j]);
		}
		printf("\n");
	}
	*/
	Bisection_method(n, A, Vector_x, Vector_y, Vector_z, norm_A_inf, input_eps, k, result);
	return 0;
}
