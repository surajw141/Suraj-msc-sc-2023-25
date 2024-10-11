#12. read a number if the number is equal to 10 or 20 or 30 divide it by 2, if the number is equal to 40 or 50 divide it by 3, else divide it by 4. Make use of a switch
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

        b = a / 2;
        printf("Result: %d\n", b);
        /* code */
        break;
    case 30:

        b = a / 2;
        printf("Result: %d\n", b);
        /* code */
        break;
    case 40:

        b = a / 3;
        printf("Result: %d\n", b);
        /* code */
        break;
    case 50:

        b = a / 3;
        printf("Result: %d\n", b);
        /* code */
        break;

    default:
        printf("Invalid input\n");
        break;
    }
}
