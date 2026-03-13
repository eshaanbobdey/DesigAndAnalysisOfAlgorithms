#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) min = j;
        }
        int temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int readFromFile(int arr[]) {
    FILE *file = fopen("C:\\Users\\ESHAAN\\OneDrive\\Desktop\\Cpp\\output\\input.txt", "r");
    if (file == NULL) return 0;
    int n = 0;
    while (fscanf(file, "%d", &arr[n]) == 1 && n < MAX) n++;
    fclose(file);
    return n;
}

int userInput(int arr[]) {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    return n;
}

int randomInput(int arr[]) {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    srand(time(0));
    for (int i = 0; i < n; i++) arr[i] = rand() % 1000;
    return n;
}

void displayArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int choice, inputChoice, arr[MAX], n;

    while (1) {
        printf("\n--- Sorting Menu ---\n");
        printf("1. Bubble Sort\n2. Selection Sort\n3. Insertion Sort\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) break;

        printf("\nChoose Input Method:\n");
        printf("1. File Input\n2. User Input\n3. Random Input\n");
        scanf("%d", &inputChoice);

        if (inputChoice == 1) n = readFromFile(arr);
        else if (inputChoice == 2) n = userInput(arr);
        else if (inputChoice == 3) n = randomInput(arr);
        else continue;

        if (n == 0) {
            printf("No data available!\n");
            continue;
        }

        printf("\nOriginal Array:\n");
        displayArray(arr, n);

        if (choice == 1) bubbleSort(arr, n);
        else if (choice == 2) selectionSort(arr, n);
        else if (choice == 3) insertionSort(arr, n);

        printf("Sorted Array:\n");
        displayArray(arr, n);
    }
    return 0;
}