#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int max(int a, int b) {
    return (a > b) ? a : b;
}


int knapsack(int W, int wt[], int val[], int n) {
    int i, w;
    int K[n + 1][W + 1];

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }

    return K[n][W];
}


void generateRandomInput(int n, int wt[], int val[], int *W) {
    for (int i = 0; i < n; i++) {
        wt[i] = rand() % 100 + 1;   
        val[i] = rand() % 200 + 1;  
    }
    *W = rand() % (n * 50) + 50;    
}


void compareTimes() {
    int sizes[] = {10, 100, 500, 1000, 2000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("\nComparing time for different random input sizes:\n");
    printf("-------------------------------------------------\n");
    printf("Items\tTime (seconds)\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int *wt = (int *)malloc(n * sizeof(int));
        int *val = (int *)malloc(n * sizeof(int));
        int W;

        generateRandomInput(n, wt, val, &W);

        clock_t start = clock();
        knapsack(W, wt, val, n);
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("%d\t%.6f\n", n, time_taken);

        free(wt);
        free(val);
    }
}

int main() {
    srand(time(0));
    int choice;

    while (1) {
        printf("\n===== 0/1 Knapsack Menu =====\n");
        printf("1. User Input\n");
        printf("2. Random Input\n");
        printf("3. Compare Times for Random Inputs\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int n, W;
            printf("Enter number of items: ");
            scanf("%d", &n);
            int wt[n], val[n];

            printf("Enter values and weights of items:\n");
            for (int i = 0; i < n; i++) {
                printf("Value[%d]: ", i + 1);
                scanf("%d", &val[i]);
                printf("Weight[%d]: ", i + 1);
                scanf("%d", &wt[i]);
            }

            printf("Enter knapsack capacity: ");
            scanf("%d", &W);

            int result = knapsack(W, wt, val, n);
            printf("Maximum value in Knapsack = %d\n", result);
        }

        else if (choice == 2) {
            int n, W;
            printf("Enter number of items: ");
            scanf("%d", &n);
            int wt[n], val[n];

            generateRandomInput(n, wt, val, &W);

            printf("Generated random data:\n");
            for (int i = 0; i < n; i++)
                printf("Item %d → Value: %d, Weight: %d\n", i + 1, val[i], wt[i]);
            printf("Knapsack Capacity: %d\n", W);

            int result = knapsack(W, wt, val, n);
            printf("Maximum value in Knapsack = %d\n", result);
        }

        else if (choice == 3) {
            compareTimes();
        }

        else if (choice == 4) {
            printf("Exiting program.\n");
            break;
        }

        else {
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}