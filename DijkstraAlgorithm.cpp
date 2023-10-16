#include <iostream>
#include <vector>
#include <limits>

// Define infinity as a constant
constexpr int INF = std::numeric_limits<int>::max();

// Function to find the vertex with the minimum distance value
int findMinDistance(const std::vector<int>& distances, const std::vector<bool>& visited) {
    int minDistance = INF;
    int minVertex = -1;

    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        if (!visited[vertex] && distances[vertex] < minDistance) {
            minDistance = distances[vertex];
            minVertex = vertex;
        }
    }

    return minVertex;
}

// Function to print the shortest path from source to each vertex
void printShortestPaths(const std::vector<int>& distances) {
    std::cout << "Vertex \t Distance from Source" << std::endl;
    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        std::cout << vertex << " \t " << distances[vertex] << std::endl;
    }
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(const std::vector<std::vector<int>>& graph, int source) {
    int V = graph.size();
    std::vector<int> distances(V, INF); // Initialize distances with infinity
    std::vector<bool> visited(V, false); // Initialize visited array

    distances[source] = 0; // Distance from the source to itself is 0

    for (int count = 0; count < V - 1; ++count) {
        int u = findMinDistance(distances, visited);
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] && distances[u] != INF &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
            }
        }
    }

    printShortestPaths(distances);
}

int main() {
    int V, E;
    std::cout << "Enter the number of vertices and edges: ";
    std::cin >> V >> E;

    std::vector<std::vector<int>> graph(V, std::vector<int>(V, 0));

    std::cout << "Enter the edge information (from to weight):" << std::endl;
    for (int i = 0; i < E; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        graph[from][to] = weight;
    }

    int source;
    std::cout << "Enter the source vertex: ";
    std::cin >> source;

    dijkstra(graph, source);

    return 0;
}
