#include <stdio.h>
int main()
{
    int arr[5];
    printf("Enter 5 integers \n");
    for (int i = 0; i < 5; i++)
    {

        printf("Enter integer %d: ", (i + 1));
        scanf("%d", &arr[i]);
    }
    printf("Given nos are :\n");
    for (int i = 0; i < 5; i++)
        printf("%d\n", arr[i]);
    return 0;
}
