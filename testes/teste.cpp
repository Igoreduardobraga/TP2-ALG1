#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

class Graph {
public:
    void Guloso(const string& startNode);
    unordered_map<string, vector<string>> grafo_guloso;
};

void Graph::Guloso(const string& startNode){
    stack<string> nodeStack;
    unordered_set<string> visitedNodes;
    int cont = 0;

    nodeStack.push(startNode);

    while (!nodeStack.empty()) {
        string currentNode = nodeStack.top();
        nodeStack.pop();

        if (grafo_guloso.count(currentNode) > 0) {
            const vector<string>& neighbors = grafo_guloso.at(currentNode);
            for (const string& neighbor : neighbors) {
                if (grafo_guloso.count(neighbor) == 0) {
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

    cout << "Número de nós visitados no lado esquerdo: " << cont << endl;
}

int main() {
    Graph graph;
    unordered_map<string, string> input = {
        {"Andre", "CFO"},
        {"Bruno", "RED"},
        {"Bruno", "SWE"},
        {"Maria", "CEO"},
        {"Maria", "CFO"},
        {"Maria", "CTO"},
        {"Paulo", "CFO"},
        {"Paulo", "CTO"},
        {"Pedro", "RED"}
    };

    for (const auto& entry : input) {
        graph.grafo_guloso[entry.first].push_back(entry.second);
    }

    string startNode = "Andre";
    graph.Guloso(startNode);

    return 0;
}