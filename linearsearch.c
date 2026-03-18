#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int readFromFile(int arr[]) {
    FILE *file = fopen("C:\\Users\\ESHAAN\\OneDrive\\Desktop\\Cpp\\output\\input.txt", "r");
    if (file == NULL) return 0;
    int n = 0;
    while (fscanf(file, "%d", &arr[n]) == 1 && n < MAX) n++;
    fclose(file);
    return n;
}

int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int main() {
    int arr[MAX], n, key, result;
    n = readFromFile(arr);
    if (n == 0) {
        printf("File not found or empty!\n");
        return 0;
    }
    printf("Enter element to search: ");
    scanf("%d", &key);
    result = linearSearch(arr, n, key);
    if (result == -1) printf("Element not found\n");
    else printf("Element found at position %d\n", result + 1);
    return 0;
}