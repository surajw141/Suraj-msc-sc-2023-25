#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N, M;

    // Input for the dimensions N and M
    printf("Enter the number of rows (N) and columns (M) for the 2D array: ");
    scanf("%d %d", &N, &M);

    // Dynamically allocate memory for the 2D array
    int **array = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
    {
        array[i] = (int *)malloc(M * sizeof(int));
    }

    // Input values for the array
    printf("Enter the values for the %dx%d array:\n", N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            scanf("%d", &array[i][j]);
        }
    }

    // Accept the position from the user
    int row, col;
    printf("Enter the row and column position (0-based indexing): ");
    scanf("%d %d", &row, &col);

    // Check if the position is within bounds
    if (row >= 0 && row < N && col >= 0 && col < M)
    {
        // Print the element at the specified position
        printf("Element at position (%d, %d): %d\n", row, col, array[row][col]);
    }
    else
    {
        printf("Invalid position. Please enter valid row and column indices.\n");
    }

    // Free dynamically allocated memory
    for (int i = 0; i < N; i++)
    {
        free(array[i]);
    }
    free(array);

    return 0;
}
