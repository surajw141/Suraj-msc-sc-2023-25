#include <stdio.h>
#include <stdlib.h>
int linear_search(int *a, int s, int x)
{
    for (int i = 0; i < s; i++)
    {
        if (a[i] == x)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    int s;
    int *a, x;
    printf("enter the size of an array.");
    scanf("%d", &s);
    a = (int *)malloc(s * sizeof(int));
    for (int i = 0; i < s; i++)
    {
        scanf("%d", &a[i]);
    }
    printf("enter the element which youy want to search: \n");
    scanf("%d", &x);
    int result = linear_search(a, s, x);
    if (result == -1)
    {
        printf("%d is not found in given array\n", x);
    }
    else
        printf("%d is found in given array at index %d \n", x, result);
}
