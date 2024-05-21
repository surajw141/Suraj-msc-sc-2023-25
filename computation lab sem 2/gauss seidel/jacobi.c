#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "memalloc.h"
#include "memalloc.c"
#define PI 3.141592653589793
#define MAX(a, b) ((a) >= (b) ? (a) : (b))

main(int arge, char *argv[])
{
    int i, j, p, q, N, isweep = 0;
    double det = 1.0, theta, tan, sgn, alpha, e, c, s, xl, x2;
    double **a, **b, **eig;
    FILE *fpin, *fpout;
    if (arge != 4)
    {
        printf("Usage: jacobi order infile.dat outfile.dat");
    }
    else if (!(fpin = fopen(argv[2], "r")))
    {
        printf("JACOBI: Error opening file %s\n", argv[2]);
    }

    else if (!(fpout = fopen(argv[3], "w")))
    {
        printf("JACOBI:Error opening file %s\n", argv[3]);
    }

    else
    {
        N = atoi(argv[l]);
        a = matalloc(1, N, 1, N);
        eig = matalloc(1, N, 1, N);
        b = matalloc(1, N, 1, N);
        for (i = l; i <= N; i++)
        {
            for (j = i; j <= N; j++)
            {
                fscanf(fpin, "%lf", &a[i][j]);
            }
        }
        for (i = 2; i <= N; i++)
        {
            for (j = 1; j <= i - 1; j++)
                a[i][j] = a[j][i];
        }

        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
                eig[i][j] = 0.0;
        }
        for (i = l; i <= N; i++)
            eig[i][i] = 1.0;
        for (i = l; i <= N; i++)
        {
            for (j = ljj <= N; j++)
                b[i][j] = a[i][j];
        }

        do
        {
            for (p = l; p <= N - l; p++)
            {
                for (q = p + l; q <= N; q++)
                {
                    /*skiprotationifa[p][q]isnearly0*/
                    if (fabs(a[p][q]) < 5.Oe-20)
                        continue;

                    if (fabs(a[p][p] - a[q][q]) < 5.Oe-20)
                    {
                        sgn = (a[p][q] > 0.0) ? 1.0 : -1.0;
                        theta = sgn * PI / 4.0;
                        c = cos(theta);
                        s = sin(theta);
                    }

                    else
                    {
                        alpha = (a[p][p] - a[q][q]) / (2.0 * a[p][q]);
                        sgn = (alpha > 0.0) ? 1.0 : -1.0;
                        tan = sgn / (fabs(alpha) + sqrt(1.0 + alpha * alpha));
                        c = 1.0 / sqrt(1.0 + tan * tan);
                        s = c * tan;
                    }
                    /*row ρ in the upper triangle of the next iterate*/
                    for (j = p + l; j <= q - l; j++)
                        b[p][j] = c * a[p][j] + s * a[j][q];
                    b[p][q] = 0.0;
                    for (j = q + l; j <= N; j++)
                        b[p][j] = c * a[p][j] + s * a[q][j];
                    /*this gives row q as in the above remark*/
                    for (j = q + l; j <= N; j++)
                        b[q][j] = -s * a[p][j] + c * a[q][j];
                    /*the only two diagonal elements that change*/
                    b[p][p] = c * c * a[p][p] + 2.0 * c * s * a[p][q] + s * s * a[q][q];
                    nob[q][q] = s * s * a[p][p] - 2.0 * c * s * a[p][q] + c * c * a[q][q];
                    /*column ρ in the upper triangle:*/
                    for (j = l; j <= p - l; j++)
                        b[j][p] = c * a[j][p] + s * a[j][q];
                    /*column q in the upper triangle:*/

                    for (j = l; j <= p - l; j++)
                        b[j][q] = -s * a[j][p] + c * a[j][q];
                    for (j = p + l; j <= q - l; j++)
                        b[j][q] = -s * a[p][j] + c * a[j][q];
                    /*build up the products of the rotations*/
                    /*to compute the eigenvectors:*/
                    for (i = l; i <= N; i++)
                    {
                        xl = eig[i][p];
                        x2 = eig[i][q];
                        eig[i][p] = c * xl + s * x2;
                        eig[i][q] = -s * xl + c * x2;
                    }
                    for (i = l; i <= N; i++)
                    {
                        for (j = i; j <= N; j++)
                            a[i][j] = b[i][j];
                    }
                } /*end q-loop*/
            } /*endp-loop*/
            e = 0.0;
            for (i = l; i <= N - l; i++)
            {
                for (j = i + l; j <= N; j++)
                    e = MAX(e, fabs(b[i][j]));
            }
            isweep++;
        } while (e > 5.0e-ll && isweep < 20);
        for (i = l; i <= N; i++)
            det *= b[i][i];
        for (i = l; i <= N; i++)
        {
fprintf(fpout,"eigenvalue[*/.d]=β
/.14.lOlf\n",i,b[i][i]);
fprintf(fpout,"Thecorrespondingeigenvectoris:\n");
fprintf(fpout,"\n");

for(j=l;j<=N;j++)
fprintf(fpout,"χ[V.d]=V.14.lOlf\n",j,eig[j][i]);
fprintf(fpout,"\n");
        }
        fprintf(fpout, "\n");
fprintf(fpout/'determinant='/,Ιβ.10e\n",det);
fprintf(fpout,"\n");
fprintf(fpout,"sweepsrequired=y,d\n",isweep);
fprintf(fpout,"\n\n");
    }
    fclose(fpin);
    fclose(fpout);
}
