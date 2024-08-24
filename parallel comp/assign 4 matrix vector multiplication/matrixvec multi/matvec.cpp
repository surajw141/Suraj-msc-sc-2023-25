#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to read matrix from file
void read_matrix(const char* filename, vector<vector<double>>& matrix, int& m, int& n) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening matrix file." << endl;
        exit(1);
    }

    infile >> m >> n;
    matrix.resize(m, vector<double>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> matrix[i][j];
        }
    }
    infile.close();
}

// Function to read vector from file
void read_vector(const char* filename, vector<double>& vec, int& n) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening vector file." << endl;
        exit(1);
    }

    infile >> n;
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        infile >> vec[i];
    }
    infile.close();
}

// Function to perform matrix-vector multiplication
vector<double> multiply_matrix_vector(const vector<vector<double>>& matrix, const vector<double>& vec) {
    int m = matrix.size();
    int n = vec.size();
    vector<double> result(m, 0.0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

int main() {
    vector<vector<double>> matrix;
    vector<double> vec;
    int m, n;

    // Read matrix and vector from files
    read_matrix("matrix.txt", matrix, m, n);
    read_vector("vector.txt", vec, n);

    // Perform matrix-vector multiplication
    vector<double> result = multiply_matrix_vector(matrix, vec);

    // Print the result
    cout << "\nMatrix-Vector Product:\n";
    for (int i = 0; i < result.size(); ++i) {
        cout << setw(4) << i << "  " << setw(10) << result[i] << "\n";
    }

    return 0;
}
