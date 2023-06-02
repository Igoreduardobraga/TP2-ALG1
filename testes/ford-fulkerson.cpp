#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
#include <queue>
#include <climits>

using namespace std;

// Estrutura para representar uma aresta com capacidade
struct Edge {
    string source;
    string destination;
    int capacity;
    int flow;
};

// Função para adicionar uma aresta em um mapa de adjacência
void addEdge(map<string, vector<Edge>>& graph, const string& source, const string& destination, int capacity) {
    Edge aresta = {source, destination, capacity, 0};
    graph[source].push_back(aresta);
    Edge aresta_arrependimento = {destination, source, 0, 0};
    graph[destination].push_back(aresta_arrependimento);
}

// Função auxiliar para verificar se existe um caminho de origem para destino no grafo residual
bool bfs(const map<string, vector<Edge>>& graph, const string& source, const string& destination, map<string, string>& parent) {
    unordered_set<string> visited;
    queue<string> q;

    q.push(source);
    visited.insert(source);
    parent[source] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        auto it = graph.find(current);
        if (it == graph.end())
            continue;

        for (const Edge& edge : it->second) {
            int residual_capacity = edge.capacity - edge.flow;
            if (visited.find(edge.destination) == visited.end() && residual_capacity > 0) {
                q.push(edge.destination);
                visited.insert(edge.destination);
                parent[edge.destination] = current;
            }
        }
    }

    return visited.find(destination) != visited.end();
}

// Função para encontrar o fluxo máximo usando o algoritmo de Ford-Fulkerson
int fordFulkerson(map<string, vector<Edge>>& graph, const string& source, const string& sink) {
    // Criar um grafo residual inicializando as capacidades residuais como as capacidades originais
    map<string, vector<Edge>> residualGraph = graph;

    map<string, string> parent;
    int maxFlow = 0;

    while (bfs(residualGraph, source, sink, parent)) {
        // int pathFlow = INT_MAX;

        // // Encontrar o fluxo máximo possível no caminho encontrado
        // for (string v = sink; v != source; v = parent[v]) {
        //     string u = parent[v];
        //     for (Edge& edge : residualGraph[u]) {
        //         if (edge.destination == v) {
        //             pathFlow = min(pathFlow, edge.capacity);
        //             break;
        //         }
        //     }
        // }

        // Atualizar as capacidades residuais no caminho encontrado
        for (string v = sink; v != source; v = parent[v]) {
            string u = parent[v];
            for (Edge& edge : residualGraph[u]) {
                if (edge.destination == v) {
                    //edge.capacity -= 1;
                    edge.flow = 1;
                    for (Edge& reverseEdge : residualGraph[v]) {
                        if (reverseEdge.destination == u) {
                            //reverseEdge.capacity += 1;
                            reverseEdge.capacity = 1;
                            reverseEdge.flow = 0;
                            break;
                        }
                    }
                    break;
                }
            }
        }

        maxFlow += 1;
    }

    return maxFlow;
}

int main() {
    map<string, vector<Edge>> graph;

    addEdge(graph, "Andre", "CFO", 1);
    addEdge(graph, "Bruno", "RED", 1);
    addEdge(graph, "Bruno", "SWE", 1);
    addEdge(graph, "Maria", "CEO", 1);
    addEdge(graph, "Maria", "CFO", 1);
    addEdge(graph, "Maria", "CTO", 1);
    addEdge(graph, "Paulo", "CFO", 1);
    addEdge(graph, "Paulo", "CTO", 1);
    addEdge(graph, "Pedro", "RED", 1);

    // Adicionar vértice de origem (source)
    string source = "source";
    addEdge(graph, source, "Andre", 1);
    addEdge(graph, source, "Bruno", 1);
    addEdge(graph, source, "Maria", 1);
    addEdge(graph, source, "Paulo", 1);
    addEdge(graph, source, "Pedro", 1);

    // Adicionar vértice de destino (sink)
    string sink = "sink";
    addEdge(graph, "CFO", sink, 1);
    addEdge(graph, "RED", sink, 1);
    addEdge(graph, "SWE", sink, 1);
    addEdge(graph, "CEO", sink, 1);
    addEdge(graph, "CTO", sink, 1);

    int cont = fordFulkerson(graph, source, sink);
    cout << cont << endl;

    // for (const auto& pair : grafo) {
    //     const vector<Edge>& edges = pair.second;
    //     for (const Edge& edge : edges) {
    //         if (edge.capacity == 1) {
    //             cout << "Edge from " << edge.source << " to " << edge.destination << " has capacity 0." << endl;
    //         }
    //     }
    // }

    return 0;
}
