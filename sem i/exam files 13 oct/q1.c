#include <stdio.h>
#include <limits.h>
int main()
{
    // a. print the size of int, float, double,
    int a = sizeof(int);
    printf("Size of Int: %d \n", a);
    float b = sizeof(float);
    printf("Size of float: %f \n", b);
    double c = sizeof(double);
    printf("Size of Double is: %lf \n", c);
    // b. Multiply the values calculated in a
    int d = a * b * c;
    printf("Multiplication of values in a is : %d \n", d);
    // c. if
    printf("%d ", d);
    if (d < 10)
    {
        printf("small number");
    }
    else if (d > 10, d < 20)
    {
        printf("big number");
    }
    else if (d > 20)
    {
        printf("Large number");
    }

    return 0;
}