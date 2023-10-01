#include <stdio.h>
int main()
{
    int b;
    printf("Enter the year to check whether it is Leap year or not: ");

    scanf("%d", &b);
    printf("you entered :%d\n", b);
    int a = b % 4;
    if (a == 0)
    {
        printf("it is leap year.\n");
        /* code */
    }
    else if (a != 0)
    {
        printf("this is Not a leap year.\n"); /* code */
    }
}