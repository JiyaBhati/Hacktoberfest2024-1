#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100  // Maximum number of vertices

int minKey(int key[], int mstSet[], int numVertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < numVertices; i++) {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
    }
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int parent[MAX_VERTICES];  // Array to store constructed MST
    int key[MAX_VERTICES];     // Key values used to pick minimum weight edge
    int mstSet[MAX_VERTICES];  // To represent the set of vertices included in MST

    // Initialize all keys as INFINITE and mstSet[] as 0
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Always include the first vertex in MST
    key[0] = 0;      // Make key 0 so that this vertex is picked as first
    parent[0] = -1;  // First node is always root of MST

    // The MST will have numVertices vertices
    for (int count = 0; count < numVertices - 1; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = minKey(key, mstSet, numVertices);
        mstSet[u] = 1;  // Add the picked vertex to the MST

        // Update key value and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < numVertices; v++) {
            // Update key only if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the constructed MST
    printMST(parent, graph, numVertices);
}

int main() {
    int numVertices;
    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    // Initialize the graph with 0s
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph[i][j] = 0;
        }
    }

    // Input the graph edges and weights
    printf("Enter the adjacency matrix (enter 0 if there is no edge):\n");
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, numVertices);

    return 0;
}
