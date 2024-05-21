#ifndef CEIDEL_HPP
#define CEIDEL_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>

#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define TOL 5.0e-10

double *vecalloc(int low, int high);
double **matalloc(int rowlow, int rowhigh, int collow, int colhigh);
double maxnum(int m, double *x);
void gauseid(int N, int *iter, double **a, double *b);

#endif // CEIDEL_HPP
