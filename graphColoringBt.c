#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int graph[MAX][MAX];
int color[MAX];
int V, M;


bool isSafe(int v, int c) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}


bool solveColoring(int v) {
    if (v == V) 
        return true;

    for (int c = 1; c <= M; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            if (solveColoring(v + 1))
                return true;
            color[v] = 0; 
        }
    }
    return false;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter number of colors (M): ");
    scanf("%d", &M);

    for (int i = 0; i < V; i++)
        color[i] = 0;

    if (solveColoring(0)) {
        printf("\nSolution exists! Coloring:\n");
        for (int i = 0; i < V; i++)
            printf("Vertex %d ---> Color %d\n", i, color[i]);
    } else {
        printf("\nNo solution exists for %d colors.\n", M);
    }

    return 0;
}