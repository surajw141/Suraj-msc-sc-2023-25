/*parallel quick sort
A = [9,,7,11,7,8,18,3,12,24,29,17,16]
partition(A, sort, end)
j = start + 1
for i = start to end
    if (A, i,j)
        swap(A, i, a)
        j = j+1
    swap (a, start , i-1)
return j - 1

QS(A, Start. end)
if(end, start, end)
if (end, start ==1)

return
else
p = partition(A, start, end)

QS(A, start, p-1)
QS(A, P+ 1, end)


*/
#include <iostream>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = low - 1; // Index of the smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; // Return the partition index
}
void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);  // Sort elements before partition
        quickSort(arr, pi + 1, high); // Sort elements after partition
    }
}

void printArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    cout << "Unsorted array: ";
    printArray(arr);

    quickSort(arr, 0, arr.size() - 1);

    cout << "Sorted array: ";
    printArray(arr);
    
    return 0;
}
