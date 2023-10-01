#include <stdio.h>

int main()
{
    int a, b;
    scanf("%d%d", &a, &b);

    if (b == 0)
    {
        printf("enter valid integer");
        /* code */
    }

    else if (b != 0)
    {
        int c = a / b;
        int d = a % b;
        printf("quotient %d\n", c);
        printf("remainder %d\n", d);
        /* code */
    }
}