#include <stdio.h>

int main()
{
  int matrix[2][2];

  // Read the matrix from the user
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      printf("Enter element [%d][%d]: ", i, j);
      scanf("%d", &matrix[i][j]);
    }
  }

  // Print the matrix
  printf("The matrix is:\n");
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}