#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

class Graph{
    private:
        unordered_map<string, vector<string>> graph;
        unordered_set<string> visitedNodes;
        int cont = 0;

    public:
        int get_count(){
            return cont;
        }

        // Função para adicionar uma aresta em um mapa de adjacência
        void addEdge(const string& node, const string& edge) {
            graph[node].push_back(edge);
        }
        // Função para executar a DFS no grafo
        void dfs(const string& startNode) {
            stack<string> nodeStack;

            nodeStack.push(startNode);

            while (!nodeStack.empty()) {
                string currentNode = nodeStack.top();
                nodeStack.pop();

                // Check if the current node exists in the graph
                if (graph.count(currentNode) > 0) {
                    const vector<string>& neighbors = graph.at(currentNode);
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
};