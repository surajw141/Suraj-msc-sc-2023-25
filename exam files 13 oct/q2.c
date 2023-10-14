#include <stdio.h>
int main()
{
    int a;
    int b;
    printf("Give two inputs for swap: ");
    scanf("%d", &a);
    scanf("%d", &b);
    printf("You have entered: %d , %d \n", a, b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("After swapping : %d ,%d \n", a, b);
    return 0;
}