#include <iostream>
#include <vector>
#include <iomanip>

// Use a large value to represent infinity (no direct edge connection)
// Choosing a value that won't overflow when added to itself
const int INF = 1e7;

// Function to print the distance matrix nicely
void printMatrix(const std::vector<std::vector<int>>& dist, int V) {
    std::cout << "Shortest distance matrix between every pair of vertices:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INF) {
                std::cout << std::setw(7) << "INF";
            } else {
                std::cout << std::setw(7) << dist[i][j];
            }
        }
        std::cout << "\n";
    }
}

// Function implementing the Floyd-Warshall algorithm
void floydWarshall(std::vector<std::vector<int>>& graph, int V) {
    // Initialize the distance matrix equal to the input graph matrix
    std::vector<std::vector<int>> dist = graph;

    /* Core Floyd-Warshall dynamic programming logic:
       k represents the intermediate vertex.
       i represents the source vertex.
       j represents the destination vertex. */
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // If vertex k is on the shortest path from i to j,
                // then update the value of dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative weight cycles
    // If distance of any vertex to itself becomes negative, a negative cycle exists
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            std::cout << "Warning: Negative weight cycle detected in the graph!\n";
            return;
        }
    }

    printMatrix(dist, V);
}

int main() {
    /* Example Graph representation (4 vertices):
          10
       (0)------->(3)
        |          ^
      5 |          | 1
        v          |
       (1)------->(2)
            3           */
    int V = 4;
    std::vector<std::vector<int>> graph = {
        {0,   5,   INF, 10},
        {INF, 0,   3,   INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    floydWarshall(graph, V);

    return 0;
}
