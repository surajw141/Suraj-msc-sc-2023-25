#include <stdio.h>
int main()
{
    int a;
    printf("Enter the number to check whether it is positive or negetive: ");

    scanf("%d", &a);
    printf("you entered :%d\n", a);
    if (a < 0)
    {
        /* code */
        printf("Value you enter is Negative\n.");
    }

    else if (a > 0)
    {
        /* code */
        printf("Value you enter is Positive.\n");
    }
    else if (a == 0)
    {
        printf("0 is nor Negative nor Positive.\n");
    }
}