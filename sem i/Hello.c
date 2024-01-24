/*#include <stdio.h>

int main() {
    printf("Hello world\n");

    return 0;
}*/

#include<windows.h>

int main() {
    int x;
    Set(20,8);
    printf("Enter a number: ");
    scanf("%d",&x);
    printf("square of %d is %d\n",x,x*x);


    return 0;
}