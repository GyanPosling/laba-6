#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<locale.h>

void getValidInput(int* value) {
    while (1) {
        if (scanf_s("%d", value) != 1) {

            while (getchar() != '\n');
            printf("Error, try again!\n");
        }
        else {
            char ch;
            if (scanf_s("%c", &ch, 1) == 1 && ch != '\n') {
                while (getchar() != '\n');
                printf("Error!! Enter again: ");
            }
            else {
                break;
            }
        }
    }
}


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void scanfArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter %d element: ", i + 1);
        getValidInput(&arr[i]);
    }
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int indexOfLastPositiveElement(int* arr, int size) {
    int lastIndex = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0) {
            lastIndex = i;
        }
    }
    return lastIndex;
}

void shellSort(int* arr, int size) {
    int lastPositiveInd = indexOfLastPositiveElement(arr, size);
    if (lastPositiveInd == -1) return;

    for (int gap = (lastPositiveInd + 1) / 2; gap > 0; gap /= 2) {
        for (int i = gap; i <= lastPositiveInd; i++) {
            if (arr[i] % 2 != 0) {

                for (int j = i; j >= gap && arr[j - gap] % 2 != 0; j -= gap) {
                    if (arr[j - gap] > arr[j]) {
                        swap(&arr[j], &arr[j - gap]);
                    }
                }
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    int size;
    do {
        printf("Enter size of array: ");
        getValidInput(&size);
        if (size > 0) {
            break;
        }
        else {
            printf("Array size can not be negative!\n ");
        }
    } while (1);

    int* arr = (int*)malloc(size * sizeof(int));

    scanfArray(arr, size);
    printf("Original Array:\n");
    printArray(arr, size);

    shellSort(arr, size);
    printf("Array after sorting:\n");
    printArray(arr, size);

    free(arr);
    return 0;
}
