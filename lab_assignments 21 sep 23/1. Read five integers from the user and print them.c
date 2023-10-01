#include <stdio.h>
int main()
{
    int a, b, c, d, e;
    printf("Enter 5 integers\n");

    printf("Enter 1st integer: ");
    scanf("%d", &a);
    printf("Enter 2nd integer: ");
    scanf("%d", &b);
    printf("Enter 3rd integer: ");
    scanf("%d", &c);
    printf("Enter 4rt integer: ");
    scanf("%d", &d);
    printf("Enter 5th integer: ");
    scanf("%d", &e);
    printf("Integers you have entered: %d, %d, %d, %d, %d.\n", a, b, c, d, e);
    return 0;
}