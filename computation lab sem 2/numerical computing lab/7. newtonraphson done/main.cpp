#include <iostream>
#include <cmath>
#include "functions.hpp"

using namespace std;

int main()
{
    double x0, tol;
    int max_iter;
    cout << "Enter the initial guess x0: ";
    cin >> x0;
    cout << "Enter the tolerance: ";
    cin >> tol;
    cout << "Enter the maximum number of iterations: ";
    cin >> max_iter;

    double root = newton_raphson(x0, tol, max_iter);
    if (!isnan(root))
    {
        cout << "Root found at x = " << root << endl;
        cout << "f(" << root << ") = " << f(root) << endl; // Verify the result
    }
    else
    {
        cout << "Method did not converge within " << max_iter << " iterations." << endl;
    }

    return 0;
}
