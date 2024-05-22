#include "MatrixClass.hpp"

int main()
{
    Matrix matrix;
    matrix.readMatrixFromUser();
    matrix.display();
    auto decompositions = matrix.lowerUpperDecomposition();

    std::cout << "Lower Matrix:" << std::endl;
    decompositions[1].display();

    std::cout << "Upper Matrix:" << std::endl;
    decompositions[0].display();

    return 0;
}
