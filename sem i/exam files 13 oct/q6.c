#include <stdio.h>

int main()
{
    // a. create a 2x 3 matrix and read this matrix from the user
    int mat[2][3];
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }

    // b. Print the first row of the matrix.
    printf("The first row of the matrix is:\n");
    for (int j = 0; j < 3; j++)
    {
        printf("%d ", mat[0][j]);
    }
    printf("\n");

    return 0;
}
