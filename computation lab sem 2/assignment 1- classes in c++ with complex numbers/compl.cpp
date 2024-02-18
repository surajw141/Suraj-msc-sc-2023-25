
#include <iostream>
#include <cmath>
#include "compl.hpp"
using namespace std;

MyComplex::MyComplex()
{
    real = 0;
    imag = 0;
}
void MyComplex::print()
{
    cout << real << " + " << imag << "i" << endl;
}
void MyComplex::add(MyComplex c1, MyComplex c2)
{
    real = c1.real + c2.real;
    imag = c1.imag + c2.imag;
}
void MyComplex::sub(MyComplex c1, MyComplex c2)
{
    real = c1.real - c2.real;
    imag = c1.imag - c2.imag;
}
void MyComplex::mult(MyComplex c1, MyComplex c2)
{
    real = c1.real * c2.real;
    imag = c1.imag * c2.imag;
}

void MyComplex::div(MyComplex c1, MyComplex c2)
{
    real = (c1.real * c2.real + c1.imag * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag);
    imag = (c1.imag * c2.real - c1.real * c2.imag) / (c2.real * c2.real + c2.imag * c2.imag);
}

void MyComplex::complexConjugate(

)
{
    imag = -1 * imag;
}
void MyComplex::norm(MyComplex c1)
{
    real = sqrt(c1.real * c1.real + c1.imag * c1.imag);
}