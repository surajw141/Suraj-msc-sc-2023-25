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
#include <stdio.h>
#include <math.h>

int main()
{
  double a, b, c;
  printf("Enter coefficients a, b, and c: ");
  scanf("%lf %lf %lf", &a, &b, &c);

  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0)
  {
    printf("Complex roots\n");
  }
  else
  {
    double root1 = (-b + sqrt(discriminant)) / (2 * a);
    double root2 = (-b - sqrt(discriminant)) / (2 * a);
    if (discriminant == 0)
    {
      printf("Real and repeated roots: %.2lf\n", root1);
    }
    else
    {
      printf("Real and distinct roots: %.2lf, %.2lf\n", root1, root2);
    }
  }

  return 0;
}
