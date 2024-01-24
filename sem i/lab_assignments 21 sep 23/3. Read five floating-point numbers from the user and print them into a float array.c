#include <stdio.h>

int main()
{
    float arr[5];

    printf("Enter 5 flaots \n");
    for (int a = 0; a < 5; a++)
    {

        printf("Enter integer %d: ", (a + 1));
        scanf("%f", &arr[a]);
    }
    printf("Given nos are :\n");
    for (int a = 0; a < 5; a++)
        printf("%f\n", arr[a]);
    return 0;
}
