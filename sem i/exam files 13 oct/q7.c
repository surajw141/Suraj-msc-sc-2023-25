#include <stdio.h>

int main()
{
    int matrix[3][3];
    int sum = 0;
    // a. 3x3 matrix from user input
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // b. Calculate the sum of the elements in the first row.
    for (int j = 0; j < 3; j++)
    {
        sum += matrix[0][j];
    }

    // c.  Check if the sum is less than 10. If it is, print "small number".
    if (sum < 10)
    {
        printf("small number\n");
    }

    return 0;
}
