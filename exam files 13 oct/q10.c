#include <stdio.h>

int main()
{
    int matrix[100][100];
    int n, row_index;

    // i and j from user.
    printf("Enter the number of rows and columns in the matrix: ");
    scanf("%d %d", &n, &n);

    // elemetn.
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    // row index.
    printf("Enter the row index that you want to print: ");
    scanf("%d", &row_index);

    // Check if the row index is valid.
    if (row_index >= 0 && row_index < n)
    {
        // Print the corresponding row of the matrix.
        printf("The row at index %d is:\n", row_index);
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[row_index][j]);
        }
        printf("\n");
    }
    else
    {
        printf("Invalid row index.\n");
    }

    return 0;
}
