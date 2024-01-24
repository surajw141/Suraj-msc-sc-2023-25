#include <iostream>
#include <cmath>
#include "compl.hpp" // Assuming you have a header file for MyComplex
using namespace std;

int main()
{
    MyComplex c1, c2, c3, result;

    cout << "Enter the real and imaginary parts of the first complex number: ";

    int i, o;
    cin >> i >> o;
    c1.real = i; // Assign directly to the member variable
    c1.imag = o;

    cout << "Enter the real and imaginary parts of the second complex number: ";
    cin >> c2.real >> c2.imag;
    c3.add(c1, c2);
    cout << "addition is performed\n";
    c3.print(); // Call the print() function of MyComplex (defined in compl.hpp) c3.print(); // Call the print() function of MyComplex (defined in compl.hpp)
    c3.sub(c1, c2);
    cout << "substraction is performed\n";
    c3.print(); // Call the print() function of MyComplex (defined in compl.hpp)

    c3.mult(c1, c2);
    cout << "multiplication is performed\n";
    c3.print(); // Call the print() function of MyComplex (defined in compl.hpp)
    c3.div(c1, c2);
    cout << "division is performed\n";
    c3.print(); // Call the print() function of MyComplex (defined in compl.hpp)
    c3.norm(c1);
    cout << "norm is performed on c1\n";
    c3.print(); // Call the print() function of MyComplex (defined in compl.hpp)
    c1.complexConjugate(c1);
    cout << "complex conjugate is performed on c1\n"; // Call the add() function of MyComplex (defined in compl.hpp)
    c1.print();                                       // Call the print() function of MyComplex (defined in compl.hpp)
    return 0;
}
