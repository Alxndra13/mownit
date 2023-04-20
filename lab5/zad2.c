#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_blas.h>

// naiwna metoda mnożenia macierzy kwadratowych
void naive_multiplication(double *A, double *B, double *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i * n + j] = 0.0;
            for (int k = 0; k < n; k++)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

// ulepszona metoda mnożenia macierzy kwadratowych
void better_multiplication(double *A, double *B, double *C, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            double r = A[i * n + k];
            for (int j = 0; j < n; j++)
            {
                C[i * n + j] += r * B[k * n + j];
            }
        }
    }
}

// funkcja do pomiaru czasu
double get_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}

// główna funkcja
int main()
{
    double *A, *B, *C, *D;
    double t1, t2, t3;

    printf("n,type,time\n");
    for (int n = 100; n < 1001; n += 100)
    {
        A = (double *)malloc(n * n * sizeof(double));
        B = (double *)malloc(n * n * sizeof(double));
        C = (double *)malloc(n * n * sizeof(double));
        D = (double *)malloc(n * n * sizeof(double));

        for (int j = 0; j < n * n; j++)
        {
            A[j] = ((double)rand() / RAND_MAX) * 10.0;
            B[j] = ((double)rand() / RAND_MAX) * 10.0;
            C[j] = 0.0;
            D[j] = 0.0;
        }

        for (int i = 0; i < 5; i++)
        {

            t1 = get_time();
            naive_multiplication(A, B, C, n);
            t1 = get_time() - t1;

            printf("%d,%s,%f\n", n, "naive", t1);

            t2 = get_time();
            better_multiplication(A, B, D, n);
            t2 = get_time() - t2;

            printf("%d,%s,%f\n", n, "better", t2);

            gsl_matrix_view a = gsl_matrix_view_array(A, n, n);
            gsl_matrix_view b = gsl_matrix_view_array(B, n, n);
            gsl_matrix_view d = gsl_matrix_view_array(D, n, n);

            t3 = get_time();
            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, &a.matrix, &b.matrix, 0.0, &d.matrix);
            t3 = get_time() - t3;

            printf("%d,%s,%f\n", n, "BLAS", t3);
        }

        free(A);
        free(B);
        free(C);
        free(D);
    }

    return 0;
}
