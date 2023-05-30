#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Classe para representar o grafo
class Graph {
    int numVertices; // Número de vértices do grafo
    vector<vector<int>> adjList; // Lista de adjacência
    vector<bool> visited; // Vetor para acompanhar os vértices visitados
    int cont;

public:
    // Construtor
    Graph(int vertices) {
        numVertices = vertices;
        adjList.resize(numVertices);
        visited.resize(numVertices);
        cont = 0;
    }

    // Função para adicionar uma aresta no grafo
    void addEdge(int source, int destination) {
        adjList[source].push_back(destination);
    }

    int get_cont(){
        return cont;
    }

    // Função principal DFS
    void DFS(int startVertex) {
        stack<int> stack; // Pilha para armazenar os vértices

        visited[startVertex] = true; // Marca o vértice inicial como visitado
        stack.push(startVertex); // Empilha o vértice inicial

        while (!stack.empty()) {
            int currentVertex = stack.top(); // Obtém o vértice no topo da pilha
            stack.pop(); // Remove o vértice da pilha

            // Percorre todos os vértices adjacentes ao vértice atual
            for (int adjacentVertex : adjList[currentVertex]) {
                if (!visited[adjacentVertex]) { // Se o vértice adjacente ainda não foi visitado
                    visited[adjacentVertex] = true; // Marca o vértice adjacente como visitado
                    stack.push(adjacentVertex); // Empilha o vértice adjacente
                    cont++;
                    break;
                }
            }
        }
    }
};

int main() {
    // Cria um objeto do tipo Graph
    Graph graph(6);

    // Adiciona arestas ao grafo
    graph.addEdge(0, 3);
    graph.addEdge(0, 4);
    graph.addEdge(1, 4);
    graph.addEdge(1, 5);
    graph.addEdge(2, 3);
    graph.addEdge(2, 5);

    graph.DFS(0);
    graph.DFS(1);
    graph.DFS(2);
    cout << graph.get_cont() << endl;

    return 0;
}
