#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *arr, int key, int start, int end);
void insertionBinarySort(int *arr, int n);

int main() {
    system("clear");

    int arr[] = {5, 2, 4, 6, 1, 3};
    int n = 6;

    insertionBinarySort(arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
}

void insertionBinarySort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int pos = binarySearch(arr, key, 0, i - 1);

        for (int j = i; j > pos; j--) {
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}

int binarySearch(int *arr, int key, int start, int end) {
    while (start <= end) {
        int mid = start + end/ 2;
        
        if (arr[mid] == key) {
            return mid;
        } else if (key > arr[mid]) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return start;
}