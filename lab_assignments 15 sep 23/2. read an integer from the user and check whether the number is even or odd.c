#include <stdio.h>
int main()
{
    int b;
    printf("Enter the number to check whether it is positive or negetive: ");

    scanf("%d", &b);
    printf("you entered :%d\n", b);
    int a = b % 2;
    if (a == 0)
    {
        printf("it is even number.\n");
        /* code */
    }
    else if (a == 1)
    {
        printf("this is odd number.\n"); /* code */
    }
}