// read an integer array from user and print it
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int *p;
    int n;
    printf("Enter the size of array:");
    scanf("%d", &n);
    p = (int *)malloc(n * sizeof(int));
    if (p == NULL)
    {
        printf("Memory not allocated");
        exit(0);
    }
    printf("Enter the elements of array:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
        printf("%d\t", p[i]);
        free(p);
        p = NULL;
    }
    return 0;
}