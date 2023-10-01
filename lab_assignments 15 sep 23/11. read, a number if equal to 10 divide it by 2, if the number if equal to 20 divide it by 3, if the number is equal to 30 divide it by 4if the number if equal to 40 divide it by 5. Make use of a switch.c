#include <stdio.h>
int main()
{
    int a;
    int b;
    scanf("%d", &a);
    switch (a)
    {
    case 10:

        b = a / 2; /* code */
        printf("Result: %d\n", b);
        break;
    case 20:

        b = a / 3;
        printf("Result: %d\n", b);
        /* code */
        break;
    case 30:

        b = a / 4;
        printf("Result: %d\n", b);
        /* code */
        break;
    case 40:

        b = a / 5;
        printf("Result: %d\n", b);
        /* code */
        break;
    default:
        printf("Invalid input\n");
        break;
    }
}