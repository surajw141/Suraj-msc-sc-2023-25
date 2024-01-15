#include <stdio.h>

int main()
{
    int n, i;
    unsigned long long fact = 1;

    printf("Enter an integer (n): ");
    scanf("%d", &n);

    // Calculate n!
    for (i = 1; i <= n; ++i)
    {
        fact *= i;
    }

    printf("%d! = %llu\n", n, fact);

    // Calculate 1/n!
    double reciprocal_fact = 1.0 / fact;
    printf("1/%d! = %e\n", n, reciprocal_fact);

    return 0;
}
