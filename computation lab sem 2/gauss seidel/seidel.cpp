#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <stdio.h>
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define TOL 5.0e-10

double *vecalloc(int low, int high)
{
    double *x;

    x = (double *)calloc((unsigned)(high - low + 1), sizeof(double));
    if (x == NULL)
    {
        fprintf(stderr, "unable to allocate memory");
        exit(1);
    }
    return (x - low);
}
double **matalloc(int rowlow, int rowhigh,
                  int collow, int colhigh)
{
    int k;
    double **x;

    x = (double **)calloc((unsigned)(rowhigh - rowlow + 1),
                          sizeof(double *));

    if (x == NULL)
    {
        fprintf(stderr, "unable to allocate memory");
        exit(1);
    }
    x -= rowlow;

    for (k = rowlow; k <= rowhigh; k++)
    {
        x[k] = (double *)calloc((unsigned)(colhigh - collow + 1),
                                sizeof(double));
        if (x[k] == NULL)
        {
            fprintf(stderr, "unable to allocate memory");
            exit(1);
        }
        x[k] -= collow;
    }
    return x;
}

double maxnum(int m, double *x)
{
    /* returns the maximum norm of vector χ */
    /* indices run over 1 to m */
    int k;
    double z;

    z = MAX(fabs(x[1]), fabs(x[2]));
    for (k = 3; k <= m; k++)
        z = MAX(fabs(x[k]), z);
    return z;
}
void gauseid(int N, int *iter, double **a, double *b)
{ /* solution returned in vector b */
    int i, j;
    double *e, *x, *y;
    double s, t;
    e = vecalloc(1, N); /* error vector */
    x = vecalloc(1, N); /* current vector approximation */
    y = vecalloc(1, N); /* next vector approximation */

    do
    {

        for (i = 1; i <= N; i++)
        {

            if (fabs(a[i][i]) < 5.0e-20)
            {
                printf("Singular matrix.");
                exit(1);
            }
            s = 0.0;
            for (j = 1; j <= i - 1; j++)
            {
                s += a[i][j] * y[j];
            }
            t = 0.0;
            for (j = i + 1; j <= N; j++)
            {
                t += a[i][j] * x[j];
            }

            y[i] = (b[i] - s - t) / a[i][i];
        }

        for (i = 1; i <= N; i++)
            e[i] = fabs(x[i] - y[i]);

        for (i = 1; i <= N; i++)
        { /* set up next iteration*/
            x[i] = y[i];
        }
        (*iter)++;
        if ((*iter) > 500)
        {
            printf("Too many iterates.");
            exit(1);
        }
    } while (maxnum(N, e) > TOL * maxnum(N, x));
    /* relative error test in maximum norm */
    for (i = 1; i <= N; i++)
    {
        b[i] = y[i];
    }
}
int main()
{
    double *vecalloc(int low, int high);
    double **matalloc(int rowlow, int rowhigh,
                      int collow, int colhigh);
    double maxnum(int m, double *x);
    void gauseid(int N, int *iter, double **a, double *x);
    double **a;
    double *b, *x;
    int iter = 0, i, j, N;
    printf("Enter the order of the matrix: ");
    scanf("%d", &N);
    printf("\n\n");
    a = matalloc(1, N, 1, N);
    b = vecalloc(1, N);
    x = vecalloc(1, N);
    printf("\n\n");
    printf("Enter the coefficient matrix A row by row:\n\n");
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            printf("a [%d,%d] = ", i, j);
            scanf("%lf", &a[i][j]);
            printf("\n\n");
        }
    }
    printf("Enter the given right-hand side b[ ]:\n\n");
    for (i = 1; i <= N; i++)
    {
        printf("b[%d] = ", i);
        scanf("%lf", &b[i]);
        printf("\n");
    }
    gauseid(N, &iter, a, b);
    for (i = 1; i <= N; i++)
    {
        printf("x[%d]=%10.10lf\n", i, b[i]);
    }
    printf("\n");

    printf("%d iterates were required. \n\n", iter);
}