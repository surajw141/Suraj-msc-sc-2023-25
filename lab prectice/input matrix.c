#include <stdio.h>

int main()
{
    int n, i, j;

    // Prompt the user for the size of the matrix (n*n)
    printf("Enter the size of the matrix (n): ");
    scanf("%d", &n);

    // Declare a 2D array to store the matrix
    int matrix[n][n];

    // Read the matrix elements from the user
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Prompt the user for the row index
    int rowIndex;
    printf("Enter the row index you want to print (0 to %d): ", n - 1);
    scanf("%d", &rowIndex);

    // Check if the row index is valid
    if (rowIndex < 0 || rowIndex >= n)
    {
        printf("Invalid row index. Please enter a valid index.\n");
    }
    else
    {
        // Print the specified row
        printf("Row %d: ", rowIndex);
        for (j = 0; j < n; j++)
        {
            printf("%d ", matrix[rowIndex][j]);
        }
        printf("\n");
    }

    return 0;
}
