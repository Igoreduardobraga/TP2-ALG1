#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// A structure to represent an edge
struct Edge {
    int u, v;
};

// A class to represent a graph object
class Graph {
    int M, N; // Number of applicants and jobs
    vector<vector<int>> adj; // Adjacency list

public:
    // Constructor
    Graph(int M, int N) : M(M), N(N) {
        adj.resize(M);
    }

    // Function to add an edge to the graph
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }

    // A DFS based recursive function
    // that returns true if a matching
    // for vertex u is possible
    bool bpm(vector<bool>& seen, vector<int>& matchR, int u) {
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (!seen[v]) {
                seen[v] = true;
                if (matchR[v] == -1 || bpm(seen, matchR, matchR[v])) {
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    // Returns maximum number
    // of matching from M to N
    int maxBPM() {
        vector<int> matchR(N, -1);
        int result = 0;
        for (int u = 0; u < M; u++) {
            vector<bool> seen(N, false);
            if (bpm(seen, matchR, u))
                result++;
        }
        return result;
    }
};

// Driver Code
int main() {
    // Let us create a Graph object
    Graph g(6, 6);

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 0);
    g.addEdge(1, 3);
    g.addEdge(2, 2);
    g.addEdge(3, 2);
    g.addEdge(3, 3);
    g.addEdge(5, 5);

    cout << "Maximum number of applicants that can get a job is " << g.maxBPM() << endl;

    return 0;
}
