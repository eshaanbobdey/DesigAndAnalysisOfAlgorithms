#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int profit, weight, bound, level;
} Node;

typedef struct {
    int profit, weight;
    double ratio;
} Item;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int W, n; 
Item items[1000];

// Bound function
int bound(Node u) {
    if (u.weight >= W) return 0;

    int profit_bound = u.profit;
    int j = u.level + 1;
    int totweight = u.weight;

    while (j < n && totweight + items[j].weight <= W) {
        totweight += items[j].weight;
        profit_bound += items[j].profit;
        j++;
    }

    if (j < n)
        profit_bound += (W - totweight) * items[j].ratio;

    return profit_bound;
}

// Priority Queue (max-heap)
Node PQ[5000];
int PQsize = 0;

void push(Node x) {
    PQ[PQsize++] = x;
    int i = PQsize - 1;

    while (i > 0 && PQ[i].bound > PQ[(i - 1) / 2].bound) {
        Node temp = PQ[i];
        PQ[i] = PQ[(i - 1) / 2];
        PQ[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

Node pop() {
    Node root = PQ[0];
    PQ[0] = PQ[--PQsize];

    int i = 0;
    while (1) {
        int largest = i;
        int left = 2 * i + 1, right = 2 * i + 2;

        if (left < PQsize && PQ[left].bound > PQ[largest].bound) largest = left;
        if (right < PQsize && PQ[right].bound > PQ[largest].bound) largest = right;
        if (largest == i) break;

        Node temp = PQ[i];
        PQ[i] = PQ[largest];
        PQ[largest] = temp;
        i = largest;
    }
    return root;
}

// Branch and Bound main function
int knapsackBB() {
    PQsize = 0;

    Node u = {-1, 0, 0, -1};
    u.bound = bound(u);
    push(u);

    int maxProfit = 0;

    while (PQsize) {
        u = pop();
        if (u.bound <= maxProfit) continue;

        Node v;
        v.level = u.level + 1;

        // Left child = include item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].profit;

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v);
        if (v.bound > maxProfit) push(v);

        // Right child = exclude item
        v.weight = u.weight;
        v.profit = u.profit;

        v.bound = bound(v);
        if (v.bound > maxProfit) push(v);
    }
    return maxProfit;
}

// Random input generator
void generateRandom(int size) {
    n = size;
    for (int i = 0; i < n; i++) {
        items[i].profit = rand() % 100 + 1;
        items[i].weight = rand() % 50 + 1;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }
}

int cmp(const void *a, const void *b) {
    double r1 = ((Item*)a)->ratio;
    double r2 = ((Item*)b)->ratio;
    return (r2 > r1) - (r2 < r1);
}

void compareTimes() {
    int sizes[] = {10, 50, 100, 200, 300};
    printf("\nSize\tTime (s)\n-------------------\n");

    for (int i = 0; i < 5; i++) {
        generateRandom(sizes[i]);
        W = sizes[i] * 10;

        qsort(items, n, sizeof(Item), cmp);

        clock_t start = clock();
        knapsackBB();
        clock_t end = clock();

        printf("%d\t%.6f\n", sizes[i], 
            (double)(end - start) / CLOCKS_PER_SEC);
    }
}

int main() {
    srand(time(0));
    int choice;

    while (1) {
        printf("\n==== Branch & Bound Knapsack ====\n");
        printf("1. User Input\n2. Random Input\n3. Compare Times\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter number of items: ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++) {
                printf("Enter profit weight of item %d: ", i + 1);
                scanf("%d %d", &items[i].profit, &items[i].weight);
                items[i].ratio = (double)items[i].profit / items[i].weight;
            }

            printf("Enter capacity: ");
            scanf("%d", &W);

            qsort(items, n, sizeof(Item), cmp);
            printf("Max Profit = %d\n", knapsackBB());
        }

        else if (choice == 2) {
            printf("Enter number of items: ");
            scanf("%d", &n);

            generateRandom(n);
            W = n * 10;

            qsort(items, n, sizeof(Item), cmp);
            printf("Max Profit = %d\n", knapsackBB());
        }

        else if (choice == 3) {
            compareTimes();
        }

        else break;
    }
}