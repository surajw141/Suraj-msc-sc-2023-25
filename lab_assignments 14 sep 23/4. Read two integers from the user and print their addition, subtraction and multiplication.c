#include<stdio.h>
int main()
{
int a, b;
printf("Give two integers: ");
scanf("%d", &a);
scanf("%d", &b);
int A = a+b;
int S = a-b;
int M = a*b;
printf("Addition of your tow integers is  : %d \n", A);
printf("Substraction of your tow integers  : %d\n", S);
printf("Multiplication of your tow integers  : %d\n", M);

return 0;
}

