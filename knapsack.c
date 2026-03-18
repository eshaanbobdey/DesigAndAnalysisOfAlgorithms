#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    double value, weight, ratio;
} Item;

void generateRandomItems(Item items[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        items[i].value = rand() % 100 + 1;
        items[i].weight = rand() % 50 + 1;
        items[i].ratio = items[i].value / items[i].weight;
    }
}

void takeUserInput(Item items[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter value and weight of item %d: ", i + 1);
        scanf("%lf %lf", &items[i].value, &items[i].weight);
        items[i].ratio = items[i].value / items[i].weight;
    }
}

int compareRatio(const void *a, const void *b) {
    double r1 = ((Item *)a)->ratio;
    double r2 = ((Item *)b)->ratio;
    return (r2 > r1) - (r2 < r1);
}

int compareValue(const void *a, const void *b) {
    double v1 = ((Item *)a)->value;
    double v2 = ((Item *)b)->value;
    return (v2 > v1) - (v2 < v1);
}

int compareWeight(const void *a, const void *b) {
    double w1 = ((Item *)a)->weight;
    double w2 = ((Item *)b)->weight;
    return (w1 > w2) - (w1 < w2);
}

double fractionalKnapsack(Item items[], int n, double capacity) {
    double totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity >= items[i].weight) {
            totalValue += items[i].value;
            capacity -= items[i].weight;
        } else {
            totalValue += items[i].value * (capacity / items[i].weight);
            break;
        }
    }
    return totalValue;
}

void testGreedyApproaches(Item items[], int n, double capacity) {
    clock_t start, end;
    double time_ratio, time_value, time_weight;
    double result_ratio, result_value, result_weight;

    Item temp[n];
    for (int i = 0; i < n; i++) temp[i] = items[i];
    start = clock();
    qsort(temp, n, sizeof(Item), compareRatio);
    result_ratio = fractionalKnapsack(temp, n, capacity);
    end = clock();
    time_ratio = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) temp[i] = items[i];
    start = clock();
    qsort(temp, n, sizeof(Item), compareValue);
    result_value = fractionalKnapsack(temp, n, capacity);
    end = clock();
    time_value = (double)(end - start) / CLOCKS_PER_SEC;

    for (int i = 0; i < n; i++) temp[i] = items[i];
    start = clock();
    qsort(temp, n, sizeof(Item), compareWeight);
    result_weight = fractionalKnapsack(temp, n, capacity);
    end = clock();
    time_weight = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nResults:\n");
    printf("1. Sort by Ratio  -> Max Value: %.2lf | Time: %.6lf s\n", result_ratio, time_ratio);
    printf("2. Sort by Value  -> Max Value: %.2lf | Time: %.6lf s\n", result_value, time_value);
    printf("3. Sort by Weight -> Max Value: %.2lf | Time: %.6lf s\n", result_weight, time_weight);
}

int main() {
    int n, choice;
    double capacity;

    while (1) {
        printf("\n==== FRACTIONAL KNAPSACK MENU ====\n");
        printf("1. User Input\n");
        printf("2. Random Input\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("Enter number of items: ");
        scanf("%d", &n);
        printf("Enter knapsack capacity: ");
        scanf("%lf", &capacity);

        Item items[n];
        if (choice == 1)
            takeUserInput(items, n);
        else if (choice == 2)
            generateRandomItems(items, n);
        else
            continue;

        testGreedyApproaches(items, n, capacity);
    }

    return 0;
}