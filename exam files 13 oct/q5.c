
#include <stdio.h>

int main()
{
    int arr[10];
    int i;
    int sum = 0;
    int rem;
    int mult = 1;
    printf("Enter an integer: ");
    for (i = 0; i < 10; i++)
    {

        scanf("%d", &arr[i]);
    }

    printf("The integers in the array are:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    for (i = 0; i < 10; i++)
    {
        sum += arr[i];
    }

    printf("Sum of the array is %d\n", sum);

    if (sum > 10)
    {
        rem = sum % 10;
        printf("it is divided by 10 and its remainder is : %d", rem);
    }

    return 0;
}