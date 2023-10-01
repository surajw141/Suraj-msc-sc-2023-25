#include <stdio.h>
#include <limits.h>

int main() {
  // Get the maximum value of all variable types 
  char max_char = CHAR_MAX;
  int max_int = INT_MAX;
  double max_double = __SIZEOF_DOUBLE__;
  float max_float = __SIZEOF_FLOAT__;
  // Print the maximum values 
  printf("The maximum value of an int variable is %d\n", max_int);
  printf("The maximum value of a float variable is %f\n", max_float);
  printf("The maximum value of a double variable is %lf\n", max_double);
  printf("The maximum value of a char variable is %d\n", max_char);
  return 0;
}