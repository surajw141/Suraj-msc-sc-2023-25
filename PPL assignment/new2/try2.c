
// C program for merge sort algorithm
// Reading input from sortinput.txt and writing output to SortedOutput.txt
#include <stdio.h>
#include <stdlib.h>

// Function to merge two sorted subarrays
void merge(int arr[], int l, int m, int r)
{
    // Print the values of the parameters on entry
    printf("Entered function merge with arr = {");
    for (int i = l; i <= r; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("}, l = %d, m = %d, r = %d\n", l, m, r);

    // Create temporary arrays to store the subarrays
    int n1 = m - l + 1;                       // Size of left subarray
    int n2 = r - m;                           // Size of right subarray
    int *L = (int *)malloc(n1 * sizeof(int)); // Allocate memory for left subarray
    int *R = (int *)malloc(n2 * sizeof(int)); // Allocate memory for right subarray

    // Check if memory allocation is successful
    if (L == NULL || R == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }

    // Copy the data to the temporary arrays
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    // Merge the temporary arrays into the original array
    int i = 0; // Index of left subarray
    int j = 0; // Index of right subarray
    int k = l; // Index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of left subarray, if any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of right subarray, if any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free the allocated memory for temporary arrays
    free(L);
    free(R);
}

// Function to perform merge sort on the array
void mergeSort(int arr[], int l, int r)
{
    // Print the values of the parameters on entry
    printf("Entered function mergeSort with arr = {");
    for (int i = l; i <= r; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("}, l = %d, r = %d\n", l, r);

    // Check if the array has more than one element
    if (l < r)
    {
        // Find the middle point of the array
        int m = l + (r - l) / 2;

        // Recursively sort the left and right halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

// Function to write the sorted array to the output file
void writeOutput(int arr[], int size)
{
    // Open the output file
    FILE *outputFile = fopen("SortedOutput.txt", "w");

    // Check if the file is opened successfully
    if (outputFile == NULL)
    {
        fprintf(stderr, "Error opening output file.\n");
        exit(1);
    }

    // Write the sorted array to the output file
    fprintf(outputFile, "Sorted Array: {");
    for (int i = 0; i < size; i++)
    {
        fprintf(outputFile, "%d", arr[i]);
        if (i < size - 1)
        {
            fprintf(outputFile, ", ");
        }
    }
    fprintf(outputFile, "}\n");

    // Close the output file
    fclose(outputFile);
}

// Main function
int main()
{
    // Open the input file
    FILE *inputFile = fopen("sortinput.txt", "r");

    // Check if the file is opened successfully
    if (inputFile == NULL)
    {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    int size;
    // Read the size of the array from the input file
    fscanf(inputFile, "Size = %d\n", &size);

    // Allocate memory for the array
    int *arr = (int *)malloc(size * sizeof(int));

    // Check if memory allocation is successful
    if (arr == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;
    }

    // Read the array elements from the input file
    fscanf(inputFile, "Elements = ");
    for (int i = 0; i < size; i++)
    {
        fscanf(inputFile, "%d", &arr[i]);
        if (i < size - 1)
        {
            fscanf(inputFile, ", ");
        }
    }

    // Close the input file
    fclose(inputFile);

    // Perform merge sort on the array
    mergeSort(arr, 0, size - 1);

    // Write the sorted array to the output file
    writeOutput(arr, size);

    // Free the allocated memory for the array
    free(arr);

    return 0;
}