#include <stdio.h>
#include <stdlib.h>

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

void merge(int* arr, int* indices, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L1 = (int*)malloc(n1 * sizeof(int));
    int* L2 = (int*)malloc(n1 * sizeof(int));
    int* R1 = (int*)malloc(n2 * sizeof(int));
    int* R2 = (int*)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) {
        L1[i] = arr[l + i];
        L2[i] = indices[l + i];
    }

    for (j = 0; j < n2; j++) {
        R1[j] = arr[m + j + 1];
        R2[j] = indices[m + j + 1];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L1[i] <= R1[j]) {
            arr[k] = L1[i];
            indices[k] = L2[i];
            i++;
        }
        else {
            arr[k] = R1[j];
            indices[k] = R2[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L1[i];
        indices[k] = L2[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R1[j];
        indices[k] = R2[j];
        j++;
        k++;
    }

    free(L1);
    free(L2);
    free(R1);
    free(R2);
}

void merge_sort(int* arr, int* indices, int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        merge_sort(arr, indices, l, mid);
        merge_sort(arr, indices, mid + 1, r);
        merge(arr, indices, l, mid, r);
    }
}

int sumOfEvenEl(int* arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

void scanMatrix(int** arr, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("Enter [%d][%d] element: ", i + 1, j + 1);
            getValidInput(&arr[i][j]);
        }
    }
}

void printMatrix(int** matrix, int N, int M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void sortMatrix(int** arr, int rows, int cols) {
    int* indices = (int*)malloc(cols * sizeof(int));
    for (int i = 0; i < cols; i++) {
        indices[i] = i;
    }

    int* sumEven = (int*)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
        int* column = (int*)malloc(rows * sizeof(int));
        for (int i = 0; i < rows; i++) {
            column[i] = arr[i][j];
        }
        sumEven[j] = sumOfEvenEl(column, rows);
        free(column);
    }

    merge_sort(sumEven, indices, 0, cols - 1);

    int** tempMatrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        tempMatrix[i] = (int*)malloc(cols * sizeof(int));
    }

    for (int j = 0; j < cols; j++) {
        int colIndex = indices[j];
        for (int i = 0; i < rows; i++) {
            tempMatrix[i][j] = arr[i][colIndex];
        }
    }

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            arr[i][j] = tempMatrix[i][j];
        }
    }

    for (int i = 0; i < rows; i++) {
        free(tempMatrix[i]);
    }
    free(tempMatrix);
    free(sumEven);
    free(indices);
}

int main() {
    int rows;
    int cols;
    printf("Enter amount of rows: ");
    getValidInput(&rows);
    printf("Enter amount of cols: ");
    getValidInput(&cols);

    int** arr = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        arr[i] = (int*)malloc(cols * sizeof(int));
    }

    scanMatrix(arr, rows, cols);
    printf("Your unsorted matrix: \n");
    printMatrix(arr, rows, cols);


    sortMatrix(arr, rows, cols);
    printf("Your sorted matrix: \n");
    printMatrix(arr, rows, cols);

    for (int i = 0; i < rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}