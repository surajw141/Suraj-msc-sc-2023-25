#include <stdio.h>
#include <limits.h>

int main()
{
    char mc = CHAR_MAX;
    int mi = INT_MAX;
    double md = __SIZEOF_DOUBLE__;
    float mf = __SIZEOF_FLOAT__;
    printf("The maximum value of an int variable is %d\n", mi);
    printf("The maximum value of an float variable is %f\n", mf);
    printf("The maximum value of an double variable is %lf\n", md);
    printf("The maximum value of an char variable is %d\n", mc);
}