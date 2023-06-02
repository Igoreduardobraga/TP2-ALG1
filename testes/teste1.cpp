#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int source;
    int destination;
    int capacity;
    int flow;
};

class Graph {
private:
    unordered_map<string, int> tabela;
    vector<vector<Edge>> adj_list;

public:
    Graph() {}

    void addVertex(const string& vertex) {
        if (tabela.find(vertex) == tabela.end()) {
            tabela[vertex] = adj_list.size();
            adj_list.emplace_back();
        }
    }

    void addEdge(const string& source, const string& destination, int capacity) {
        int srcIndex = tabela[source];
        int destIndex = tabela[destination];

        Edge forwardEdge = {srcIndex, destIndex, capacity, 0};
        Edge backwardEdge = {destIndex, srcIndex, 0, 0};
        adj_list[srcIndex].push_back(forwardEdge);
        adj_list[destIndex].push_back(backwardEdge);
    }

    void printGraph() {
        for (const auto& entry : tabela) {
            const string& vertex = entry.first;
            int vertexIndex = entry.second;

            cout << "Adjacency list of vertex " << vertex << ": ";
            for (const Edge& edge : adj_list[vertexIndex]) {
                for (const auto& vertexEntry : tabela) {
                    if (vertexEntry.second == edge.destination) {
                        cout << vertexEntry.first << " ";
                        break;
                    }
                }
            }
            cout << endl;
        }
    }

    bool bfs(int source, int sink, vector<int>& parent) {
        vector<bool> visited(adj_list.size(), false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (const Edge& edge : adj_list[current]) {
                int neighbor = edge.destination;
                if (!visited[neighbor] && edge.capacity > edge.flow) {
                    q.push(neighbor);
                    parent[neighbor] = current;
                    visited[neighbor] = true;
                }
            }
        }

        return visited[sink];
    }

    int fordFulkerson() {

        int source = tabela["source"];
        int sink = tabela["sink"];
        vector<int> parent(adj_list.size(), -1);
        int maxFlow = 0;

        while (bfs(source, sink, parent)) {

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                for (Edge& edge : adj_list[u]) {
                    if (edge.destination == v) {
                        edge.flow++;
                        break;
                    }
                }

                for (Edge& edge : adj_list[v]) {
                    if (edge.destination == u) {
                        edge.flow--;
                        break;
                    }
                }
            }

            maxFlow++;
        }

        return maxFlow;
    }
};

int main() {
    Graph graph;

    graph.addVertex("Andre");
    graph.addVertex("Bruno");
    graph.addVertex("Maria");
    graph.addVertex("Paulo");
    graph.addVertex("Pedro");
    graph.addVertex("CFO");
    graph.addVertex("RED");
    graph.addVertex("SWE");
    graph.addVertex("CEO");
    graph.addVertex("CTO");
    graph.addVertex("source");
    graph.addVertex("sink");

    graph.addEdge("Andre", "CFO", 1);
    graph.addEdge("Bruno", "RED", 1);
    graph.addEdge("Bruno", "SWE", 1);
    graph.addEdge("Maria", "CEO", 1);
    graph.addEdge("Maria", "CFO", 1);
    graph.addEdge("Maria", "CTO", 1);
    graph.addEdge("Paulo", "CFO", 1);
    graph.addEdge("Paulo", "CTO", 1);
    graph.addEdge("Pedro", "RED", 1);

    string source = "source";
    graph.addEdge(source, "Andre", 1);
    graph.addEdge(source, "Bruno", 1);
    graph.addEdge(source, "Maria", 1);
    graph.addEdge(source, "Paulo", 1);
    graph.addEdge(source, "Pedro", 1);

    // Adicionar vértice de destino (sink)
    string sink = "sink";
    graph.addEdge("CFO", sink, 1);
    graph.addEdge("RED", sink, 1);
    graph.addEdge("SWE", sink, 1);
    graph.addEdge("CEO", sink, 1);
    graph.addEdge("CTO", sink, 1);

    //graph.printGraph();

    int maxFlow = graph.fordFulkerson();
    cout << "Max Flow: " << maxFlow << endl;

    return 0;
}
