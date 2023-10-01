#include <stdio.h>

int main()
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    if (a >= b >= c)
    {
        printf("largest value is %d\n", a);
        /* code */
    }
    else if (b >= c)
    {
        printf("largest value is %d\n", b);
        /* code */
    }
    else if (c >= b)
    {
        printf("largest value is %d\n", c);
        /* code */
    }

    return 0;
}