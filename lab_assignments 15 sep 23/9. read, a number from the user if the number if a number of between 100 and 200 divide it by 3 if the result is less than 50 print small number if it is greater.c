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