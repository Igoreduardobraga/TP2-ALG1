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

void Graph::addEdge_exato(const string& source, const string& destination) {
    if (!edgeExists_exato(source, destination)) {
        Edge aresta_grafo = {source, destination, 1, 0};
        grafo_exato[source].push_back(aresta_grafo);

        // Adicionar aresta de arrependimento (volta)
        Edge aresta_arrependimento = {destination, source, 0, 0};
        grafo_exato[destination].push_back(aresta_arrependimento);

        // Adicionar o destino no conjunto de destinos do vértice de origem
        destinos_exato[source].insert(destination);

        // Adicionar o destino no conjunto de destinos do vértice de destino (aresta de arrependimento)
        destinos_exato[destination].insert(source);
    }
}

bool Graph::edgeExists_exato(const string& source, const string& destination) {
    // Verificar se o vértice de origem existe no grafo
    if (grafo_exato.find(source) == grafo_exato.end()) {
        return false;  // O vértice de origem não existe no grafo
    }

    // Verificar se o vértice de destino existe no grafo
    if (grafo_exato.find(destination) == grafo_exato.end()) {
        return false;  // O vértice de destino não existe no grafo
    }

    // Verificar se o vértice de destino já existe no conjunto de destinos do vértice de origem
    const unordered_set<string>& destinos = destinos_exato[source];
    return (destinos.find(destination) != destinos.end());
}

bool Graph::bfs(const unordered_map<string, vector<Edge>>& grafo_residual, const string& source, const string& destination, unordered_map<string, string>& parent) {
    unordered_set<string> visited;
    queue<string> q;

    q.push(source);
    visited.insert(source);
    parent[source] = "";

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        auto it = grafo_residual.find(current);
        if (it == grafo_residual.end())
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

int Graph::Exato(const string& source, const string& sink) {
// Criar um grafo residual inicializando as capacidades residuais como as capacidades originais
    unordered_map<string, vector<Edge>> residualGraph = grafo_exato;

    unordered_map<string, string> parent;
    int maxFlow = 0;

    //auto start = std::chrono::high_resolution_clock::now(); // Obter o horário de início
    while (bfs(residualGraph, source, sink, parent)) {
        // Atualizar as capacidades residuais no caminho encontrado
        string v = sink;
        while (v != source) {
            string u = parent[v];
            for (Edge& edge : residualGraph[u]) {
                if (edge.destination == v) {
                    edge.flow = 1;
                    for (Edge& reverseEdge : residualGraph[v]) {
                        if (reverseEdge.destination == u) {
                            reverseEdge.capacity = 1;
                            reverseEdge.flow = 0;
                            break;
                        }
                    }
                    break;
                }
            }
            v = u;
        }

        maxFlow++;
    }

    //auto end = std::chrono::high_resolution_clock::now(); // Obter o horário de término

    // // Calcular a duração em segundos
    // std::chrono::duration<double> duration = end - start;
    // double seconds = duration.count();
    // cout << "Tempo de execução: " << seconds << " segundos" << endl;

    return maxFlow;
}
