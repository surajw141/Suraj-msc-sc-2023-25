#include "bisection.hpp"

int main()
{
    float a, b, e;
    std::cout << "Enter the initial guesses\na = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "\nEnter the accuracy\n";
    std::cin >> e;

    bisection(a, b, e);

    return 0;
}
