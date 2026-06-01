#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];
char vertexName[MAX];

// Read graph from file
void readGraphFromFile(char filename[], int *n) {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        exit(1);
    }

    // Read number of vertices
    fscanf(fp, "%d", n);

    // Read vertex names like A B C D E
    for (int i = 0; i < *n; i++) {
        fscanf(fp, " %c", &vertexName[i]);
    }

    // Read adjacency matrix
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }

    fclose(fp);
}

// Convert letter to index
int getIndex(char ch, int n) {
    for (int i = 0; i < n; i++) {
        if (vertexName[i] == ch) {
            return i;
        }
    }
    return -1;
}

// Reset visited array before BFS or DFS
void resetVisited(int n) {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

// DFS using recursion
void DFS(int vertex, int n) {
    visited[vertex] = 1;
    printf("%c ", vertexName[vertex]);

    for (int i = 0; i < n; i++) {
        if (graph[vertex][i] == 1 && visited[i] == 0) {
            DFS(i, n);
        }
    }
}

// BFS using queue
void BFS(int start, int n) {
    int front = -1, rear = -1;
    int current;

    visited[start] = 1;
    queue[++rear] = start;

    printf("BFS Traversal: ");

    while (front != rear) {
        current = queue[++front];
        printf("%c ", vertexName[current]);

        for (int i = 0; i < n; i++) {
            if (graph[current][i] == 1 && visited[i] == 0) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

int main() {
    int n;
    char startChar;
    int start;

    readGraphFromFile("graph.txt", &n);

    printf("Enter starting vertex: ");
    scanf(" %c", &startChar);

    start = getIndex(startChar, n);

    if (start == -1) {
        printf("Invalid starting vertex.\n");
        return 0;
    }

    resetVisited(n);
    BFS(start, n);

    resetVisited(n);
    printf("\nDFS Traversal: ");
    DFS(start, n);

    return 0;
}