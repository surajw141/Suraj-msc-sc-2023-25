#include <stdio.h>
int main()
{
    char mat[3][3];
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Enter element [%d][%d]: ", i, j);
            scanf("%c", &mat[i][j]);
        }
    }

    printf("The first row of the matrix is: \n");
    for (int j = 0; j < 3; j++)
    {
        printf("%c ", mat[0][j]);
    }
    printf("\n");
    return 0;
}