#include "MatrixClass.hpp"

void Matrix::guassSeidel(){
    if (!isDiagonallyDominant())
        //Try to make the matrix DD
        makeDiagonallyDominant();
    bool flag = true;
    int count = 0;
    double var[cols-1],prev,sum = 0.0;
    for (int i = 0; i < cols-1; i++){
        // initailise the vallues of the variables to 0
        var[i] = 0;
    }
    // Condition : |P{n+1}-P{n}| <= Tolerance
    while(flag){
        prev = var[0];
        for(int r = 0; r < rows; r++){
            double lhs = 0.0;
            for (int c = 0; c < cols-1; c++){
                if (r != c){
                    lhs += mat[r][c]*var[c];
                }
            }
            lhs = (-1)*lhs + mat[r][cols-1];
            //current values of the variables
            var[r] = lhs/mat[r][r];
        }

        // for (int k = 0; k < cols-1; k++){
        //     sum += pow(prev[k]-var[k],2);
        // }

        sum = pow(prev-var[0],2);
        // cout << sqrt(sum) << endl;
        // cout << TOLERANCE << endl << endl;

        if (sqrt(sum) <= TOLERANCE){
            flag = false;
        }
        count++;
    }
    cout << "Iterations for Seidel ::" << count << endl;
    for (int i = 0; i < cols-1; i++){
            // print the values
            cout << var[i] << endl;
    }
}