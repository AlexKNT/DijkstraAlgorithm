#include <iostream>
#include <vector>
#include <limits>

constexpr int INF = std::numeric_limits<int>::max();

// Function to find the vertex with the minimum distance value
/*
This is a function that takes two arguments - distances and visited. distances is a vector that stores the current known distances from the source vertex to all other vertices, and visited is a vector that keeps track of which vertices have been visited or processed in the Dijkstra algorithm.
*/
int findMinDistance(const std::vector<int>& distances, const std::vector<bool>& visited) {
    int minDistance = INF;
    int minVertex = -1;

    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        if (!visited[vertex] && distances[vertex] < minDistance) {
            minDistance = distances[vertex]; // Update minimum distance
            minVertex = vertex; // Update the vertex with the minimum distance
        }
    }

    return minVertex; // Return the vertex with the minimum distance
}


// Function to print the shortest paths from the source to each vertex
void printShortestPaths(const std::vector<int>& distances) {
    std::cout << "Vertex \t Distance from Source\n";
    for (int vertex = 0; vertex < distances.size(); ++vertex) {
        std::cout << vertex << " \t " << distances[vertex] << '\n';
    }
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(const std::vector<std::vector<int>>& graph, int source) {
    int V = graph.size();
    std::vector<int> distances(V, INF); // Initialize distances with infinity
    std::vector<bool> visited(V, false); // Initialize visited array

    distances[source] = 0; // Distance from the source to itself is 0

    /*
     It iterates to ensure that all vertices have been processed and their shortest distances have been determined. The loop's purpose is to find the shortest paths from the source to all other vertices.
    */
    for (int count = 0; count < V - 1; ++count) {
        int u = findMinDistance(distances, visited); // Find the vertex with the minimum distance
        visited[u] = true; // Mark the selected vertex as visited

        // Update distances to neighboring vertices
        for (int v = 0; v < V; ++v) {
            // Update distance if the vertex is not visited, there's a direct edge,
            // and if the new path through 'u' is shorter
            if (!visited[v] && graph[u][v] && distances[u] != INF &&
                distances[u] + graph[u][v] < distances[v]) {
                /*
                If all conditions are met, it calculates the potential new distance to v through u by adding the distance from the source to u (distances[u]) and the weight of the edge from u to v (graph[u][v]). If this new distance is smaller than the current known distance to v (distances[v]), it updates distances[v] with the new, shorter distance. This step essentially compares whether the path from the source to v through u is shorter than the currently known path to v.
                */
                distances[v] = distances[u] + graph[u][v];
            }
        }
    }

    printShortestPaths(distances); // Print the shortest distances from the source
}


// Function to run a predefined test case
void runTest() {
    // Example graph represented as an adjacency matrix
    std::vector<std::vector<int>> graph = {
        {0, 4, 2, 0, 0},
        {0, 0, 5, 10, 0},
        {0, 0, 0, 3, 2},
        {0, 0, 0, 0, 8},
        {0, 0, 0, 0, 0}
    };
    int source = 0;

    std::cout << "Test Case 1 (Custom Test):\n";
    std::cout << "Source Vertex: " << source << '\n';
    dijkstra(graph, source);
}

int main() {
    int choice;
    std::cout << "Choose an option:\n1. Enter your own graph\n2. Run a test case\n";
    std::cin >> choice;

    if (choice == 1) {
        int V, E;
        std::cout << "Enter the number of vertices: ";
        std::cin >> V;

        std::cout << "Enter the number of edges: ";
        std::cin >> E;

        std::vector<std::vector<int>> graph(V, std::vector<int>(V, 0));

        std::cout << "Enter the edge information (from to weight):\n";
        for (int i = 0; i < E; ++i) {
            int from, to, weight;
            std::cin >> from >> to >> weight;
            graph[from][to] = weight;
        }

        int source;
        std::cout << "Enter the source vertex: ";
        std::cin >> source;

        dijkstra(graph, source);
    }
    else if (choice == 2) {
        runTest();
    }
    else {
        std::cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}
