#include <stdio.h>
#include <math.h>

int main()
{
  int a, b, c;
  float x, y;
  scanf("%d", &a);
  scanf("%d", &b);
  scanf("%d", &c);

  // x2 - 7x+10=0
  // x = (-b ± √(b^2 - 4ac)) / 2a
  x = ((-b) + sqrt((b)*b - 4 * a * c)) / 2 * a;
  y = ((-b) - sqrt((b)*b - 4 * a * c)) / 2 * a;
  printf("%f\n", x);
  printf("%f\n", y);
  return 1;
}
/*#include <stdio.h>
#include <math.h>

// Calculates the roots of a quadratic equation using the quadratic formula.
void find_roots(float a, float b, float c, float *root1, float *root2) {
  float discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
    *root1 = (-b + sqrt(discriminant)) / (2 * a);
    *root2 = (-b - sqrt(discriminant)) / (2 * a);
  } else if (discriminant == 0) {
    *root1 = *root2 = -b / (2 * a);
  } else {
    printf("The quadratic equation has no real roots.\n");
    return;
  }
}

int main() {
  float a, b, c;

  printf("Enter the coefficients of the quadratic equation: ");
  scanf("%f %f %f", &a, &b, &c);

  float root1, root2;

  find_roots(a, b, c, &root1, &root2);

  printf("The roots of the quadratic equation are: %f, %f\n", root1, root2);

  return 0;
}
*/