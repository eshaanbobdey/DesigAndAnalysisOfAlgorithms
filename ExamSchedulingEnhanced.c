#include <stdio.h>
#include <stdbool.h>

void welshPowellScheduling(int n, int graph[n][n]) {
    int degree[n], color[n], order[n];

    
    for (int i = 0; i < n; i++) {
        degree[i] = 0;
        for (int j = 0; j < n; j++)
            if (graph[i][j] == 1)
                degree[i]++;
        order[i] = i;
    }

    
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (degree[order[j]] > degree[order[i]]) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    
    for (int i = 0; i < n; i++)
        color[i] = 0;

    int slot = 0;
    bool available[n];

    
    for (int k = 0; k < n; k++) {
        int exam = order[k];
        if (color[exam] != 0)
            continue;

        slot++;
        color[exam] = slot;

        for (int i = k + 1; i < n; i++) {
            int next = order[i];
            if (color[next] == 0) {
                bool conflict = false;
                for (int j = 0; j < n; j++) {
                    if (graph[next][j] == 1 && color[j] == slot) {
                        conflict = true;
                        break;
                    }
                }
                if (!conflict)
                    color[next] = slot;
            }
        }
    }

    
    printf("\nExam Scheduling (Welsh–Powell Algorithm):\n");
    for (int i = 0; i < n; i++)
        printf("Exam %d → Time Slot %d\n", i + 1, color[i]);

    printf("\nMinimum number of time slots required: %d\n", slot);
}

int main() {
    int n;
    printf("Enter number of exams: ");
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("Invalid number of exams.\n");
        return 1;
    }

    int graph[n][n];
    printf("\nEnter the adjacency matrix (1 if conflict, 0 otherwise):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    welshPowellScheduling(n, graph);
    return 0;
}