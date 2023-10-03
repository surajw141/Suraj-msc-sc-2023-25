#include <stdio.h>
#include <math.h>
int main()
{
    int a, b, c;
    float x, y;
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    x = ((-b) + sqrt((b)*b - 4 * a * c)) / 2 * a;
    y = ((-b) + sqrt((b)*b - 4 * a * c)) / 2 * a;
    printf("%f\n", x);
    printf("%f\n", y);
    return 1;
}