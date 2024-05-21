#include "ceidel.hpp"

double *vecalloc(int low, int high)
{
    double *x = (double *)calloc((high - low + 1), sizeof(double));
    if (x == NULL)
    {
        std::cerr << "Unable to allocate memory" << std::endl;
        exit(1);
    }
    return (x - low);
}

double **matalloc(int rowlow, int rowhigh, int collow, int colhigh)
{
    int k;
    double **x = (double **)calloc((rowhigh - rowlow + 1), sizeof(double *));
    if (x == NULL)
    {
        std::cerr << "Unable to allocate memory" << std::endl;
        exit(1);
    }
    x -= rowlow;

    for (k = rowlow; k <= rowhigh; k++)
    {
        x[k] = (double *)calloc((colhigh - collow + 1), sizeof(double));
        if (x[k] == NULL)
        {
            std::cerr << "Unable to allocate memory" << std::endl;
            exit(1);
        }
        x[k] -= collow;
    }
    return x;
}

double maxnum(int m, double *x)
{
    double z = MAX(fabs(x[1]), fabs(x[2]));
    for (int k = 3; k <= m; k++)
    {
        z = MAX(fabs(x[k]), z);
    }
    return z;
}

void gauseid(int N, int *iter, double **a, double *b)
{
    int i, j;
    double *e, *x, *y;
    double s, t;
    e = vecalloc(1, N);
    x = vecalloc(1, N);
    y = vecalloc(1, N);

    do
    {
        for (i = 1; i <= N; i++)
        {
            if (fabs(a[i][i]) < 5.0e-20)
            {
                std::cerr << "Singular matrix." << std::endl;
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
        {
            e[i] = fabs(x[i] - y[i]);
        }

        for (i = 1; i <= N; i++)
        {
            x[i] = y[i];
        }

        (*iter)++;
        if ((*iter) > 500)
        {
            std::cerr << "Too many iterates." << std::endl;
            exit(1);
        }
    } while (maxnum(N, e) > TOL * maxnum(N, x));

    for (i = 1; i <= N; i++)
    {
        b[i] = y[i];
    }
}
