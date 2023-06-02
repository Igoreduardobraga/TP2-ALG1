#include "graph.hpp"

Graph::Graph(){
    cont = 0;
}

void Graph::Guloso(const string& startNode){
    stack<string> nodeStack;

    nodeStack.push(startNode);

    while (!nodeStack.empty()) {
        string currentNode = nodeStack.top();
        nodeStack.pop();

        // Check if the current node exists in the graph
        if (grafo_guloso.count(currentNode) > 0) {
            const vector<string>& neighbors = grafo_guloso.at(currentNode);
            for (const string& neighbor : neighbors) {
                if (visitedNodes.find(neighbor) == visitedNodes.end()) {
                    nodeStack.push(neighbor);
                    visitedNodes.insert(neighbor);
                    cont++; 
                    break;
                }
            }
        }
    }
}

void Graph::addEdge_guloso(const string& node, const string& edge){
    grafo_guloso[node].push_back(edge);
}

void Graph::addVertex(const string& vertex) {
    if (tabela.find(vertex) == tabela.end()) {
        tabela[vertex] = adj_list.size();
        adj_list.emplace_back();
    }
}

void Graph::addEdge(const string& source, const string& destination) {
    int srcIndex = tabela[source];
    int destIndex = tabela[destination];
    Edge forwardEdge = {srcIndex, destIndex, 1, 0};
    Edge backwardEdge = {destIndex, srcIndex, 0, 0};

    // Verificar se a aresta já existe
    bool edgeExists = false;
    for (const Edge& edge : adj_list[srcIndex]) {
        if (edge.destination == destIndex) {
            edgeExists = true;
            break;
        }
    }

    if (!edgeExists) {
        adj_list[srcIndex].push_back(forwardEdge);
        adj_list[destIndex].push_back(backwardEdge);
    }
}

bool Graph::bfs(int source, int sink, vector<int>& parent) {
    vector<bool> visited(adj_list.size(), false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    bool found = false; // Variável para controlar se o nó de destino foi encontrado

    while (!q.empty() && !found) {
        int current = q.front();
        q.pop();

        for (const Edge& edge : adj_list[current]) {
            int neighbor = edge.destination;
            if (!visited[neighbor] && edge.capacity > edge.flow) {
                q.push(neighbor);
                parent[neighbor] = current;
                visited[neighbor] = true;

                if (neighbor == sink) {
                    found = true; // Nó de destino encontrado, interrompe a busca
                    break;
                }
            }
        }
    }

    return visited[sink] && found; // Retorna true se o nó de destino foi encontrado e visitado
}

int Graph::fordFulkerson() {

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