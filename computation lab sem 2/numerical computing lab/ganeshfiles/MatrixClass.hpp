#ifndef MATRIX_CLASS_HPP
#define MATRIX_CLASS_HPP
#define TOLERANCE pow(10, -5)

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
#define TOLERANCE pow(10, -5)

class Matrix
{
    // double **mat;
    // int rows,cols;
public:
    double **mat;
    int rows, cols;
    // construct object(s)
    Matrix();
    Matrix(int, int);
    Matrix(const Matrix &);

    // Free up memory
    ~Matrix();

    // Standard Operations
    //  void printMatrix(double**,int, int);
    void display();
    void readMatrixViaFiles(string, string);
    void readMatrixFromUser();

    // Check for nature of matrix
    bool isNull();
    bool isSymmetric();
    bool isDiagonallyDominant();
    bool makeDiagonallyDominant();

    // helper functions
    double getLii(int, double **);
    double getLij(int, int, double **);
    vector<vector<double>> transpose();
    int getDDRow(int);
    void swapRows(int, int);
    double computeL(double **, double **, double **, int, int);
    double computeU(double **, double **, double **, int, int);

    // template<class T, std::size_t S>
    // void backSubstitution(T **,T(&) [S]);
    void backSubstitution(double **, double *); // size of ans array is not known untill runtime!
    void forwardSubstitution(double **, double *);

    // Operations on matrices
    void addition(Matrix, Matrix);
    void substraction(Matrix, Matrix);
    void multiply(Matrix, Matrix);

    // Functions on augmented matrices
    void guassianElimination();
    vector<Matrix> lowerUpperDecomposition();
    vector<Matrix> choleskyDecomposition();
    void guassJacobi();
    void guassSeidel();
};
#endif // MATRIX_CLASS_HPP
