
#include <stdio.h>

int main()
{
    int arr[5];

    for (int i = 0; i < 10; i++)
    {
        printf("Enter an integer %d \n: ", i);
        scanf("%d", &arr[i]);
    }

    printf("The integers in the array are:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

/*#include <stdio.h>

int main()
{
    int arr[5];

    for (int i = 0; i < 10; i++)
    {
        printf("Enter an integer: ");
        scanf("%d", &arr[i]);
    }

    printf("The integers in the array are:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}*/