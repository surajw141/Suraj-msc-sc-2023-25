#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>

using namespace std;

#define TOLERANCE 0.0001

class Matrix
{
private:
    double **mat;
    int rows;
    int cols;

    bool isDiagonallyDominant();
    bool makeDiagonallyDominant();
    int getDDRow(int row);
    void swapRows(int r1, int r2);

public:
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix &other);
    ~Matrix();

    void readMatrixViaFiles(string fileL, string fileR);
    void display();
    void guassSeidel();
};

#endif
