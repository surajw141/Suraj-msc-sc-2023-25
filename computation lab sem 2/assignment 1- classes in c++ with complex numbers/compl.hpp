class MyComplex
{
private:
    /* data */
public:
    double real;
    double imag;

    // default constructor
    MyComplex();

    void print();
    void add(MyComplex, MyComplex);
    void sub(MyComplex, MyComplex);
    void mult(MyComplex, MyComplex);
    void div(MyComplex, MyComplex);
    void norm(MyComplex);
    void complexConjugate();
};
