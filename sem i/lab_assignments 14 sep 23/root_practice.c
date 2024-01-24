#include <stdio.h>
#include <math.h>
int main()
{
    int a, b, c;
    int x, y;
    printf("enter three variables :");
    scanf("%d%d%d", &a, &b, &c);

    // for x = -b + sqrt(+b*b-4*a*c)/2+a

    x = (-b + sqrt((+b * b) - 4 * a * c)) / 2 * a;

    y = (-b - sqrt((+b * b) - 4 * a * c)) / 2 * a;
    printf("root 1 is %d\n", x);
    printf("root 2 is %d\n", y);
    return 0;
}