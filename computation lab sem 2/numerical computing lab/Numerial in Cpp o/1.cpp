#include <bits/stdc++.h>
#include <vector>
using namespace std;

class GaussianElimination {
    int row;
    int col;
    vector<vector<double>> mat;

public:
    GaussianElimination(vector<vector<double>> &matrix) {
        mat = matrix;
        row = matrix.size();
        col = matrix[0].size();
    }

    void printMatrix() {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                cout << " " << mat[i][j] << "\n";
            }
            cout << "\n";
        }
    }

    void rowReduction() {
        int r = 0;
        while (r < row) {
            double pivot = mat[r][r];
            for (int i = 0; i < col; i++) {
                if (pivot != 0) {
                    mat[r][i] /= pivot;
                }
            }
            for (int i = 0; i < row; i++) {
                if (i != r) {
                    double tmp = mat[i][r];
                    for (int j = 0; j < col; j++) {
                        mat[i][j] -= tmp * mat[r][j];
                    }
                }
            }
            r++;
        }
    }

    void backSubstitution() {
        vector<double> ans(row);
        for (int r = row - 1; r >= 0; r--) {
            double lhs = 0;
            for (int c = col - 2; c > r; c--) {
                lhs += mat[r][c] * ans[c];
            }
            ans[r] = mat[r][col - 1] - lhs;
        }
        ofstream outFile("output.txt");
        if (outFile.is_open()) {
            for (int i = 0; i < row; i++) {
                outFile << ans[i] << endl;
            }
            outFile.close();
        } else {
            cerr << "open output file.";
        }
    }

    void gaussianElimination() {
        rowReduction();
        backSubstitution();
    }
};

int main() {
    ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        cerr << "open input file.";
        return 1;
    }

    int rows, cols;
    inFile >> rows >> cols;

    vector<vector<double>> matrix(rows, vector<double>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            inFile >> matrix[i][j];
        }
    }
    inFile.close();

    GaussianElimination sol(matrix);
    sol.gaussianElimination();

    return 0;
}