#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000

int graph[MAX][MAX];
int visited[MAX];
int n;

void readGraphFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    fscanf(file, "%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(file, "%d", &graph[i][j]);

    fclose(file);
    printf("Graph successfully loaded from file!\n");
}

void takeUserInput() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
}

void generateRandomGraph(int size) {
    n = size;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = (rand() % 2); 
            if (i == j)
                graph[i][j] = 0; 
        }
    }
    printf("Random graph of size %d generated.\n", n);
}

void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int node = queue[front++];
        for (int i = 0; i < n; i++) {
            if (graph[node][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

void DFSUtil(int node) {
    visited[node] = 1;
    for (int i = 0; i < n; i++) {
        if (graph[node][i] && !visited[i])
            DFSUtil(i);
    }
}

void DFS(int start) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    DFSUtil(start);
}

void compareTimes() {
    clock_t start_time, end_time;
    double bfs_time, dfs_time;

    start_time = clock();
    BFS(0);
    end_time = clock();
    bfs_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    start_time = clock();
    DFS(0);
    end_time = clock();
    dfs_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nExecution Time Comparison:\n");
    printf("BFS Time: %.6lf seconds\n", bfs_time);
    printf("DFS Time: %.6lf seconds\n\n", dfs_time);
}

int main() {
    int choice, size;

    while (1) {
        printf("\n===== GRAPH MENU =====\n");
        printf("1. Input graph from file\n");
        printf("2. Input graph manually\n");
        printf("3. Generate random graph\n");
        printf("4. Perform BFS\n");
        printf("5. Perform DFS\n");
        printf("6. Compare BFS & DFS Times\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            readGraphFromFile("graph.txt");
            break;
        case 2:
            takeUserInput();
            break;
        case 3:
            printf("Enter size of random graph: ");
            scanf("%d", &size);
            generateRandomGraph(size);
            break;
        case 4:
            BFS(0);
            printf("BFS completed from node 0.\n");
            break;
        case 5:
            DFS(0);
            printf("DFS completed from node 0.\n");
            break;
        case 6:
            compareTimes();
            break;
        case 7:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}