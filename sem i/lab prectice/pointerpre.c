#include <stdio.h>
int main()
{
    int x = 5;
    int *j;
    j = &x;

    printf("%d\n", x);
    printf("%d \n", *j);
    printf("%u", *&j);
}