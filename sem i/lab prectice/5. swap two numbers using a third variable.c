#include <stdio.h>
int main()
{
    int a, b;
    printf("Give first integer\n a : ");
    scanf("%d", &a);
    printf("Give second integer\n a : ");
    scanf("%d", &b);
    printf("integers you gave as input : a = %d, b = %d\n", a, b);
    int c = a;
    a = b;
    b = c;
    printf("swapped integers are : a = %d, b = %d \n", a, b);

    return 0;
}