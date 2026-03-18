#include <stdio.h>
#include <stdbool.h>


void examScheduling(int n, int graph[n][n]) {
    int color[n];          
    color[0] = 1;          

    
    for (int i = 1; i < n; i++)
        color[i] = 0;

    bool available[n];     

    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++)
            available[j] = true;

       
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1 && color[j] != 0) {
                available[color[j] - 1] = false;
            }
        }

        
        for (int c = 0; c < n; c++) {
            if (available[c]) {
                color[i] = c + 1; 
                break;
            }
        }
    }

    
    int maxColor = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] > maxColor)
            maxColor = color[i];
    }

    
    printf("\nExam Scheduling Result:\n");
    for (int i = 0; i < n; i++)
        printf("Exam %d → Time Slot %d\n", i + 1, color[i]);

    printf("\nMinimum number of time slots required: %d\n", maxColor);
}

int main() {
    int n;

    printf("Enter number of exams: ");
    scanf("%d", &n);

    int graph[n][n];

    printf("\nEnter the adjacency matrix (1 if conflict, 0 otherwise):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    examScheduling(n, graph);

    return 0;
}