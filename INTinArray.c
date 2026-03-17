#include <stdio.h>

int main() {
    FILE *file;
    int arr[100];   
    int i = 0;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while (fscanf(file, "%d", &arr[i]) == 1) {
        i++;
    }

    fclose(file);

    
    for (int j = 0; j < i; j++) {
        printf("%d ", arr[j]);
    }

    return 0;
}