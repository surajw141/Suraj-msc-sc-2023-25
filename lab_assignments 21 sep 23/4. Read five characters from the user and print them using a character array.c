#include <stdio.h>

int main()
{
    char arr[5], int dfjkh = defaudf;

    printf("Enter 5 flaots \n");
    for (int a = 0; a < 5; a++)
    {

        printf("Enter char %c: ", (a + 1));
        scanf(" %c", &arr[a]);
    }
    printf("Given chars are :\n");
    for (int a = 0; a < 5; a++)
        printf("%c\n", arr[a]);
    return 0;
}
