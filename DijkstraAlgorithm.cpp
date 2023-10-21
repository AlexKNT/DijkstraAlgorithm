#include <iostream>  // Include for standard input and output operations
#include <vector>    // Include for using vector data structure
#include <limits>    // Include for using numeric limits to define 'INF'

constexpr int INF = std::numeric_limits<int>::max();  // Define 'INF' as the maximum possible integer value

/**
 * @brief Find the vertex with the minimum distance that has not been visited.
 *
 * @param distances - Vector of distances from the source vertex to each vertex.
 * @param visited - Vector indicating whether each vertex has been visited.
 * @return int - The index of the vertex with the minimum distance.
 */
int findMinDistance(const std::vector<int>& distances, const std::vector<bool>& visited) {
    int minDistance = INF;  // Initialize minDistance with 'INF'
    int minVertex = -1;     // Initialize minVertex with an invalid value

    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        if (!visited[vertex] && distances[vertex] < minDistance) {
            minDistance = distances[vertex];
            minVertex = vertex;
        }
    }

    return minVertex;  // Return the index of the vertex with the minimum distance
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
 * @brief Perform Dijkstra's algorithm to find the shortest paths from a source vertex.
 *
 * @param graph - 2D vector representing the graph with edge weights.
 * @param source - The source vertex for which shortest paths are calculated.
 */
void dijkstra(const std::vector<std::vector<int>>& graph, int source) {
    int V = graph.size();  // Get the number of vertices in the graph
    std::vector<int> distances(V, INF);  // Initialize distances to all vertices as 'INF'
    std::vector<bool> visited(V, false);  // Initialize all vertices as not visited

    distances[source] = 0;  // Set the distance to the source vertex as 0

    for (int count = 0; count < V - 1; ++count) {
        int u = findMinDistance(distances, visited);  // Find the vertex with the minimum distance
        visited[u] = true;  // Mark the vertex as visited

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[u][v] && distances[u] != INF &&
                distances[u] + graph[u][v] < distances[v]) {
                distances[v] = distances[u] + graph[u][v];  // Update the distance if a shorter path is found
            }
        }
    }

    printShortestPaths(distances);  // Print the shortest distances from the source vertex
}

/**
 * @brief Check if a vertex is within the valid range.
 *
 * @param vertex - The vertex to check.
 * @param maxVertex - The maximum valid vertex index.
 * @return bool - True if the vertex is valid, false otherwise.
 */
bool isValidVertex(int vertex, int maxVertex) {
    return vertex >= 0 && vertex < maxVertex;  // Check if the vertex is within the valid range
}

int main() {
    int numVertices, numEdges;

    std::cout << "Enter the number of vertices: ";
    std::cin >> numVertices;

    std::cout << "Enter the number of edges: ";
    std::cin >> numEdges;

    std::vector<std::vector<int>> graph;
    graph.resize(numVertices, std::vector<int>(numVertices, 0));  // Initialize the graph with all edges having weight 0

    std::cout << "Enter the edge information (from to weight):\n";  // Prompt the user to enter edge information
    for (int i = 0; i < numEdges; ++i) {  // Loop through each edge input
        int from, to, weight;  // Declare variables to store edge information

        std::cout << "Edge " << i + 1 << ": ";  // Prompt the user to enter edge number
        std::cin >> from >> to >> weight;  // Read input for 'from', 'to', and 'weight' from the user

        if (isValidVertex(from, numVertices) && isValidVertex(to, numVertices)) {
            // Check if 'from' and 'to' vertices are within the valid range (0 to numVertices-1)
            graph[from][to] = weight;  // Set the weight of the edge from 'from' to 'to'
            graph[to][from] = weight;  // Assuming it's an undirected graph, set the weight in both directions
        }
        else {
            std::cout << "Invalid edge input. Please enter valid from and to vertices within the range [0, " << numVertices - 1 << "].\n";
            // Display an error message for invalid input
            i--;  // Decrement 'i' to retry input for the current edge
        }
    }


    int source;
    std::cout << "Enter the source vertex: ";
    std::cin >> source;

    dijkstra(graph, source);  // Perform Dijkstra's algorithm

    return 0;
}
