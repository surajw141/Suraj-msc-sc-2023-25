#include<stdio.h>
int main()
{
    float a,b,c,d,e,sum;
    printf("Give five integers: ");
    scanf("%f %f %f %f %f",&a,&b,&c,&d,&e);
    sum = a+b+c+d+e;
    printf("Addition of integers is %f\n",sum);
    if (sum>10)
    {
        sum= sum/2;
        printf("Here addition is greater than 10 so it is divided by 2 therefor: %f\n",sum);

    }
    else
    {
        sum=sum/3;
        printf("Here addition is less than 10 so it is  dividen by 3 therefore: %f\n",sum);
    }

}