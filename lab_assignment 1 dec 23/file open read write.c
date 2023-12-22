// write a code that read elements from a file and print them in a output file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    // Open files for reading and writing
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    char str[100];

    // Read lines from input file using fgets
    while (fgets(str, 100, input) != NULL)
    {
        // Write same line to output file
        fputs(str, output);
    }

    // Close files
    fclose(input);
    fclose(output);
    return 0;
}