#include<stdio.h>

int main() {
    int a;
    float b;
    double c;
    long double d;
    char e;

    printf("Give integer: ");
    scanf("%d", &a);

    printf("Give float: ");
    scanf("%f", &b);

    printf("Give double: ");
    scanf("%lf", &c);

    printf("Give long double: ");
    scanf("%Lf", &d);


    printf("Give char: ");
    scanf(" %c", &e); 

    printf("here is %d\n", a);
    printf("here is %f\n", b);
    printf("here is %lf\n", c);
    printf("here is %Lf\n", d);
    printf("here is %c\n", e);

    return 0;
}


