#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>
#include <algorithm>

using namespace std;

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &A, int start, int end)
{
    int pivot = A[start];
    int j = start + 1;

    for (int i = start + 1; i <= end; i++)
    {
        if (A[i] < pivot)
        {
            swap(A[i], A[j]);
            j++;
        }
    }
    swap(A[start], A[j - 1]);
    return j - 1;
}

void quickSort(vector<int> &A, int start, int end)
{
    if (start < end)
    {
        int p = partition(A, start, end);
        quickSort(A, start, p - 1);
        quickSort(A, p + 1, end);
    }
}

void gatherSortedParts(int rank, int size, vector<int> &localArray, vector<int> &sortedArray, int localSize)
{
    MPI_Gather(localArray.data(), localSize, MPI_INT,
               sortedArray.data(), localSize, MPI_INT, 0, MPI_COMM_WORLD);
}

vector<int> mergeSortedArrays(const vector<int> &left, const vector<int> &right)
{
    vector<int> result;
    auto i = left.begin(), j = right.begin();

    while (i != left.end() && j != right.end())
    {
        if (*i < *j)
        {
            result.push_back(*i++);
        }
        else
        {
            result.push_back(*j++);
        }
    }

    while (i != left.end())
    {
        result.push_back(*i++);
    }

    while (j != right.end())
    {
        result.push_back(*j++);
    }

    return result;
}

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    vector<int> A;
    if (rank == 0)
    {
        // Reading numbers from file
        ifstream inputFile("numbers.txt");
        int num;
        while (inputFile >> num)
        {
            A.push_back(num);
        }
        inputFile.close();
    }

    int n = A.size();
    int localSize = n / size;

    vector<int> localArray(localSize);
    MPI_Scatter(A.data(), localSize, MPI_INT, localArray.data(), localSize, MPI_INT, 0, MPI_COMM_WORLD);

    quickSort(localArray, 0, localSize - 1);

    vector<int> sortedArray;
    if (rank == 0)
    {
        sortedArray.resize(n);
    }

    gatherSortedParts(rank, size, localArray, sortedArray, localSize);

    if (rank == 0)
    {
        vector<int> finalSortedArray;
        for (int i = 0; i < size; i++)
        {
            vector<int> part(sortedArray.begin() + i * localSize, sortedArray.begin() + (i + 1) * localSize);
            if (finalSortedArray.empty())
            {
                finalSortedArray = part;
            }
            else
            {
                finalSortedArray = mergeSortedArrays(finalSortedArray, part);
            }
        }

        // Writing sorted numbers to file
        ofstream outputFile("sorted_numbers.txt");
        for (const auto &num : finalSortedArray)
        {
            outputFile << num << " ";
        }
        outputFile.close();

        cout << "Sorted numbers written to 'sorted_numbers.txt'." << endl;
    }

    MPI_Finalize();
    return 0;
}
