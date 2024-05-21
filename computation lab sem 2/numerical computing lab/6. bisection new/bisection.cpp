#include "bisection.hpp"

float f(float x)
{
    return x * x - 4.0;
}

void bisection(float a, float b, float e)
{
    std::cout.precision(5);
    std::cout.setf(std::ios::fixed);

    float c, fa, fb, fc;
    int iter = 0;

    if (f(a) * f(b) < 0)
    {
        std::cout << "Iter" << std::setw(14) << "a" << std::setw(14) << "b" << std::setw(14) << "c" << std::setw(14) << "f(c)" << std::setw(14) << "|a-b|" << std::endl;
        std::cout << "\n----------------------------------------------------------------------\n";

        while (fabs(a - b) >= e)
        {
            c = (a + b) / 2.0;
            fa = f(a);
            fb = f(b);
            fc = f(c);
            iter++;
            std::cout << iter << std::setw(14) << a << std::setw(14) << b << std::setw(14) << c << std::setw(14) << fc << std::setw(14) << fabs(a - b) << std::endl;

            if (fc == 0)
            {
                std::cout << "Root of equation is " << c << std::endl;
                return;
            }

            if (fa * fc > 0)
            {
                a = c;
            }
            else if (fa * fc < 0)
            {
                b = c;
            }
        }

        std::cout << "\nRoot is " << c << std::endl;
    }
    else
    {
        std::cout << "Enter different initials" << std::endl;
    }
}
