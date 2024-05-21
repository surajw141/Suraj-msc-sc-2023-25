#include "ceidel.hpp"
#include <iomanip>

int main()
{
    double **a, *b, *x;
    int iter = 0, i, j, N;

    std::cout << "Enter the order of the matrix: ";
    std::cin >> N;

    a = matalloc(1, N, 1, N);
    b = vecalloc(1, N);
    x = vecalloc(1, N);

    std::cout << "Enter the coefficient matrix A row by row:\n";
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            std::cout << "a[" << i << "," << j << "] = ";
            std::cin >> a[i][j];
        }
    }

    std::cout << "Enter the given right-hand side b[]:\n";
    for (i = 1; i <= N; i++)
    {
        std::cout << "b[" << i << "] = ";
        std::cin >> b[i];
    }

    gauseid(N, &iter, a, b);

    std::cout << std::fixed << std::setprecision(4);
    for (i = 1; i <= N; i++)
    {
        std::cout << "x[" << i << "] = " << b[i] << std::endl;
    }

    std::cout << iter << " iterates were required." << std::endl;

    return 0;
}
