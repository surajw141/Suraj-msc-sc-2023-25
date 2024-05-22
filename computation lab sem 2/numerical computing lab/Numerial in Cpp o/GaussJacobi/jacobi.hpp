class Matrix {
private:
    int rows;
    int cols;
    double **mat;

public:
    Matrix();
    Matrix(int r, int c);
    ~Matrix();
    void Readfiles();
    int getDDRowAt(int r);
    void gaussJacobi(vector<double> &initialGuess, double tol, int maxIter);
    int getRows() const { return rows; }
    int getCols() const { return cols; }
};