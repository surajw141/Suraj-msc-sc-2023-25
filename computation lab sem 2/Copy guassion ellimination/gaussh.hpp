// Matrixops.h
#ifndef MATRIXops_H
#define MATRIXops_H

#include <iostream>
#include <fstream>
using namespace std;

class Matrixops
{
private:
    double **mat;
    int rows, cols;

public:
    Matrixops();
    ~Matrixops();
    void readMatrix(const string &filename_l, const string &filename_r);
    void printMatrix();
    void uppertriangular();
    void backSubstitution();
};

#endif
