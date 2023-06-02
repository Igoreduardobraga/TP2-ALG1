#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

// Structure to represent an edge
struct Edge {
    int v;          // destination vertex
    int capacity;   // capacity of the edge
    int flow;       // current flow through the edge
    int rev;        // reverse index of the edge
};

// Class to represent the graph
class Graph {
    int V;              // number of vertices in the graph
    vector<vector<Edge>> adj;   // adjacency list

public:
    // Constructor
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v, int capacity) {
        Edge e1 = {v, capacity, 0, adj[v].size()};
        Edge e2 = {u, 0, 0, adj[u].size()};  // reverse edge with zero capacity
        adj[u].push_back(e1);
        adj[v].push_back(e2); // reverse edge
    }

    // Function to find the maximum flow using the Ford-Fulkerson algorithm
    int fordFulkerson(int source, int sink) {
        // Initialize all flows to zero
        for (int u = 0; u < V; u++) {
            for (Edge& e : adj[u]) {
                e.flow = 0;
            }
        }

        // Execute the Ford-Fulkerson algorithm using the Edmonds-Karp algorithm
        int maxFlow = 0;
        while (bfs(source, sink)) {
            vector<int> path(V, 0);
            int pathFlow = INT_MAX;
            int v = sink;

            // Find the maximum flow along the augmenting path found by BFS
            while (v != source) {
                int u = path[v];
                for (Edge& e : adj[u]) {
                    if (e.v == v) {
                        pathFlow = min(pathFlow, e.capacity - e.flow);
                        break;
                    }
                }
                v = u;
            }

            // Update the flows of the edges along the augmenting path
            v = sink;
            while (v != source) {
                int u = path[v];
                for (Edge& e : adj[u]) {
                    if (e.v == v) {
                        e.flow += pathFlow;
                        adj[v][e.rev].flow -= pathFlow;  // update the reverse edge
                        break;
                    }
                }
                v = u;
            }

            // Add the flow of the augmenting path to the maximum flow
            maxFlow += pathFlow;
        }

        // Return the maximum flow
        return maxFlow;
    }

    // Function to access the adjacency list and print the residual capacities of the edges
    void printResidualCapacities() {
        for (int u = 0; u < V; u++) {
            for (const Edge& e : adj[u]) {
                cout << "Edge (" << u << " -> " << e.v << "): Residual capacity = " << e.capacity - e.flow << endl;
            }
        }
    }

private:
    // Breadth-First Search (BFS) function to find an augmenting path
    bool bfs(int source, int sink) {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        queue<int> q;

        visited[source] = true;
        q.push(source);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge& e : adj[u]) {
                int v = e.v;
                if (!visited[v] && e.capacity > e.flow) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                }
            }
        }

        // Return true if there is an augmenting path to the sink vertex
        return visited[sink];
    }
};

int main() {
    int V = 4; // number of vertices

    Graph graph(V);

    // Adding the edges to the graph
    graph.addEdge(0, 1, 3);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 3);

    int source = 0;  // source vertex
    int sink = 3;    // sink vertex

    // Find the maximum flow using the Ford-Fulkerson algorithm
    int maxFlow = graph.fordFulkerson(source, sink);

    cout << "Maximum flow: " << maxFlow << endl;

    // Print the residual capacities of the edges
    graph.printResidualCapacities();

    return 0;
}
