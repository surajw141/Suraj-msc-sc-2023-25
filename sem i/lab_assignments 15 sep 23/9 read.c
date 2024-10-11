#9. read, a number from the user if the number if a number of between 100 and 200 divide it by 3 if the result is less than 50 print small number if it is greater

#include <stdio.h>
int main()
{
    int a, b;

    scanf("%d", &a);

    if (a > 100, a < 200)
    {
        b = (a / 3);
        if (b < 50)
        {
            printf("small number %d\n", b);
        }
        else if (b > 50)
        {
            printf("not so big number%d\n", b);
        }
    }
    /* code */

    else if (a > 200, a < 300)
    {
        b = (a / 2);
        if (b > 110)
        {
            printf("result %d\n", b);
        }
        else
        {
            b = a / 5;
            printf("result %d\n", b);
        }
    }
    else if (a > 300)
    {
        printf("Very big number: %d\n", a);

        /* code */
    }
    return 0;
}
