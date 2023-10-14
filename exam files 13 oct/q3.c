#include <stdio.h>
#include <math.h>
// #define PI 3.14159265358979323846

int main()
{
    float radius, area;

    // radius from user.
    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    // formula.
    area = 3.14 * radius * radius;

    // area of the circle.
    printf("The area of the circle is: %f\n", area);

    return 0;
}
