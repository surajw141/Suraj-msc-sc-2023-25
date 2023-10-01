#include<stdio.h>
int main()
{
int a, b;
printf("Give first integer\n a: ");
scanf("%d", &a);
printf("Give first integer\n b: ");
scanf("%d", &b);
printf("intergers you gave as input : a = %d, b = %d \n",a,b );
a = a + b;
b = a - b;
a = a - b;
printf("swapped integers are  : a = %d, b = %d \n",a,b );

return 0;
}

