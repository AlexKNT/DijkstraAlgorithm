#include <iostream>
#include <vector>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

/**
 * @brief Find the vertex with the minimum distance that has not been visited.
 *
 * @param distances - Vector of distances from the source vertex to each vertex.
 * @param visited - Vector indicating whether each vertex has been visited.
 * @return int - The index of the vertex with the minimum distance.
 */
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

/**
 * @brief Print the shortest distances from the source to all vertices.
 *
 * @param distances - Vector of distances from the source vertex to each vertex.
 */
void printShortestPaths(const std::vector<int>& distances) {
    std::cout << "Vertex \t Distance from Source\n";
    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        std::cout << vertex << " \t " << distances[vertex] << '\n';
    }
}

/**
 * @brief Log the current iteration's state for debugging purposes.
 *
 * @param iteration - The current iteration number.
 * @param distances - Vector of distances from the source vertex to each vertex.
 * @param visited - Vector indicating whether each vertex has been visited.
 */
void logIteration(int iteration, const std::vector<int>& distances, const std::vector<bool>& visited) {
    std::cout << "Iteration " << iteration << ":\n";
    std::cout << "Vertex \t Distance \t Visited\n";
    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        std::cout << vertex << " \t " << distances[vertex] << " \t " << (visited[vertex] ? "Yes" : "No") << '\n';
    }
    std::cout << "------------------------\n";
}

/**
 * @brief Perform Dijkstra's algorithm to find the shortest paths from a source vertex.
 *
 * @param graph - 2D vector representing the graph with edge weights.
 * @param source - The source vertex for which shortest paths are calculated.
 */
void dijkstra(const std::vector<std::vector<int>>& graph, int source) {
    int V = graph.size();
    std::vector<int> distances(V, INF);
    std::vector<bool> visited(V, false);

    distances[source] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = findMinDistance(distances, visited);
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] && distances[u] != INF &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];
            }
        }

        logIteration(count + 1, distances, visited);
    }

    printShortestPaths(distances);
}

/**
 * @brief Check if a vertex is within the valid range.
 *
 * @param vertex - The vertex to check.
 * @param maxVertex - The maximum valid vertex index.
 * @return bool - True if the vertex is valid, false otherwise.
 */
bool isValidVertex(int vertex, int maxVertex) {
    return vertex >= 0 && vertex < maxVertex;
}

int main() {
    int numVertices, numEdges;

    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    std::vector<std::vector<int>> graph;
    graph.resize(numVertices, std::vector<int>(numVertices, 0));

    std::cout << "Enter the edge information (from to weight):\n";
    for (int i = 0; i < numEdges; ++i) {
        int from, to, weight;

        std::cout << "Edge " << i + 1 << ": ";
        std::cin >> from >> to >> weight;

        if (isValidVertex(from, numVertices) && isValidVertex(to, numVertices)) {
            graph[from][to] = weight;
            graph[to][from] = weight;
        }
        else {
            std::cout << "Invalid edge input. Please enter valid from and to vertices within the range [0, " << numVertices - 1 << "].\n";
            i--;
        }
    }

    int source;
    std::cout << "Enter the source vertex: ";
    std::cin >> source;

    dijkstra(graph, source);

    return 0;
}
