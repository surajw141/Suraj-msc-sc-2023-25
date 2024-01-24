#include <stdio.h>
int main()
{
    int arr[5];
    int sum = 0;
    printf("Enter 5 integers \n");
    for (int i = 0; i < 5; i++)
    {
        printf("Enter integer %d: ", (i + 1));
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    printf("The sum of the entered integers is: %d\n", sum);

    return 0;
}
/*#include <stdio.h>

int main() {
    int arr[5];
    int sum = 0;

    printf("Enter 5 integers:\n");

    for (int i = 0; i < 5; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &arr[i]);
        sum += arr[i];
    }

    printf("The sum of the entered integers is: %d\n", sum);

    return 0;
}
*/